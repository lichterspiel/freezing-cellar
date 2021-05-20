#include "stage.h"

void initStage()
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0 , sizeof(stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
    stage.explosionTail = &stage.explosionHead;

    bulletTexture = loadTexture("gfx/bullet.png");
    enemyTexture = loadTexture("gfx/enemy.png");
    alienBulletTexture = loadTexture("gfx/bullet.png");
    playerTexture = loadTexture("gfx/bulb.png");
    explosionTexture = loadTexture("gfx/explosion.png");
    pointsTexture = loadTexture("gfx/points.png");

    resetStage();


}

static void resetStage()
{
    Entity* e;
    Explosion* ex;
    Debris* d;

    while(stage.fighterHead.next)
    {
        e = stage.fighterHead.next;
        stage.fighterHead.next = e->next;
        free(e);
    }

    while (stage.bulletHead.next)
    {
        e = stage.bulletHead.next;
        stage.bulletHead.next = e->next;
        free(e);
    }

    while (stage.explosionHead.next)
    {
        ex = stage.explosionHead.next;
        stage.explosionHead.next = ex->next;
        free(ex);
    }

    while (stage.debrisHead.next)
    {
        d = stage.debrisHead.next;
        stage.debrisHead.next = d->next;
        free(d);
    }

    while (stage.pointsHead.next)
    {
        e = stage.pointsHead.next;
        stage.pointsHead.next = e->next;
        free(e);
    }

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
    stage.debrisTail = &stage.debrisHead;
    stage.pointsTail = &stage.pointsHead;

    initPlayer();

    enemySpawnTimer = 0;

    stageResetTimer = FPS * 3;

    stage.score = 0;
}

static void initPlayer()
{
    player = malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    stage.fighterTail->next = player;
    stage.fighterTail = player;

    player->health = 1;
    player->x = 100;
    player->y = 100;
    player->texture = playerTexture;
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

    player->side = SIDE_PLAYER;
}

static void initStarfield()
{
    int i;

    for (i = 0; i < MAX_STARS; i++)
    {
        stars[i].x = rand() % SCREEN_WIDTH;
        stars[i].y = rand() % SCREEN_WIDTH;
        stars[i].speed = 1 + rand() % 8;
    }
}

static void logic()
{
    doBackground();

    doStarfield();

    doPlayer();

    doFighters();

    doEnemies();

    doBullets();

    doExplosions();

    doDebris();

    doPointsPods();

    spawnEnemies();

    clipPlayer();

    if (player == NULL && --stageResetTimer <= 0)
    {
        resetStage();
    }
}


static void doPlayer()
{
    if (player != NULL)
    {
        player->dx = player->dy = 0;

        if (player->reload > 0)
        {
            player->reload--;
        }
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_D])
        {
            player->dx = PLAYER_SPEED;
        }
        if (state[SDL_SCANCODE_A])
        {
            player->dx = -PLAYER_SPEED;
        }
        if (state[SDL_SCANCODE_W])
        {
            player->dy = -PLAYER_SPEED;
        }
        if (state[SDL_SCANCODE_S])
        {
            player->dy = PLAYER_SPEED;
        }
        // handle shooting
        if (state[SDL_SCANCODE_L] && player->reload == 0)
        {
            playSound(SND_PLAYER_FIRE, CH_PLAYER);

            fireBullet();
        }

    }
}

static void doFighters()
{
    Entity *e, *prev;

    prev = &stage.fighterHead;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;

        if (e != player && e->x < -e->w)
        {
            e->health = 0;
        }

        if (e->health == 0)
        {
            if (e == player)
            {
                player = NULL;
            }

            if (e == stage.fighterTail)
            {
                stage.fighterTail = prev;
            }

             prev->next = e->next;
             free(e);
             e = prev;
        }

        prev = e;
    }
}

static void doBullets()
{
    Entity* b;
    Entity* prev;

    prev = &stage.bulletHead;

    for (b = stage.bulletHead.next; b != NULL; b = b->next)
    {
        b->x += b->dx;
        b->y += b->dy;

        if(bulletHitFighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT)
        {
            if (b == stage.bulletTail)
            {
                stage.bulletTail = prev;
            }

            prev->next = b->next;
            free(b);
            b = prev;
        }

        prev = b;
    }
}

static void doExplosions()
{
    Explosion *e, *prev;

    prev = &stage.explosionHead;

    for (e = stage.explosionHead.next ; e != NULL ; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;

        if (--e->a <= 0)
        {
            if (e == stage.explosionTail)
            {
                stage.explosionTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}

static void doDebris()
{

    Debris *d, *prev;

    prev = &stage.debrisHead;

    for (d = stage.debrisHead.next ; d != NULL ; d = d->next)
    {
        d->x += d->dx;
        d->y += d->dy;

        d->dy += 0.5;

        if (--d->life <= 0)
        {
            if (d == stage.debrisTail)
            {
                stage.debrisTail = prev;
            }
            prev->next = d->next;
            free(d);
            d = prev;
        }
        prev = d;
    }
}

static void doPointsPods()
{
    Entity *e, *prev;

    prev = &stage.pointsHead;

    // go through linked list
    for (e = stage.pointsHead.next; e != NULL; e = e->next)
    {
        // check if it hit border and if so make the dx or dy negative to bounce
        if (e->x < 0 )
        {
            e->x = 0;
            e->dx = -e->dx;
        }
        if (e->x + e->w > SCREEN_WIDTH)
        {
            e->x = SCREEN_WIDTH - e->w;
            e->dx = -e->dx;
        }
        if (e->y < 0)
        {
            e->y = 0;
            e->dy = -e->dy;
        }
        if (e->y + e->h > SCREEN_HEIGHT)
        {
            e->y = SCREEN_HEIGHT - e->h;
            e->dy = -e->dy;
        }

        e->x += e->dx;
        e->y += e->dy;

        //check if pod made contact with player;
        if (player != NULL && collision(e->x, e->y, e->w, e->h, player->x, player->y, player->w, player->h))
        {
            e->health = 0;

            stage.score++;

            highscore = MAX(stage.score, highscore);

            playSound(SND_POINTS, CH_POINTS);
        }

        // if it never hits the player delete it
        if (--e->health <= 0)
        {
            if (e == stage.pointsTail)
            {
                stage.pointsTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}

static void addPointsPod(int x, int y)
{
    // create Entity and add it to the linked list
    Entity* e;
    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.pointsTail->next = e;
    stage.pointsTail = e;

    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    // live 10 seconds
    e->health = FPS * 10;
    e->texture = pointsTexture;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

    e->x -= e->w / 2;
    e->y -= e->h / 2;

}

static void spawnEnemies()
{
    Entity* enemy;

    if (--enemySpawnTimer <= 0)
    {
        enemy = malloc(sizeof(Entity));
        memset(enemy, 0, sizeof(Entity));
        stage.fighterTail->next = enemy;
        stage.fighterTail = enemy;

        enemy->x = SCREEN_WIDTH;
        enemy->y = rand() % SCREEN_HEIGHT - 64;
        enemy->texture = enemyTexture;
        enemy->health = 1;
        SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

        enemy->dx = -(2 + (rand() % 4));
        enemy->dy = -100 + (rand() % 200);
        enemy->dy /= 100;
        enemy->side = SIDE_ALIEN;

        enemy->reload = FPS * (1 + (rand() % 3));

        enemySpawnTimer = 30 + (rand() % 60);
    }
}

static void addExplosions(int x, int y, int num)
{
    Explosion* e;
    int i;

    for (i = 0; i < num; i++)
    {
        e = malloc(sizeof(Explosion));
        memset(e, 0, sizeof(Explosion));
        stage.explosionTail->next = e;
        stage.explosionTail = e;

        e->x = x + (rand() % 32) - (rand() % 32);
        e->y = y + (rand() % 32) - (rand() % 32);
        e->dx = (rand() % 10) - (rand() % 10);
        e->dy = (rand() % 10) - (rand() % 10);

        e->dx /= 10;
        e->dy /= 10;

        switch (rand() % 4)
        {
            case 0:
                e->r = 255;
                break;

            case 1:
                e->r = 255;
                e->g = 128;
                break;

            case 2:
                e->r = 255;
                e->g = 255;
                break;

            default:
                e->r = 255;
                e->g = 255;
                e->b = 255;
                break;
        }

        e->a = rand() % FPS * 3;
    }
}

static void addDebris(Entity* e)
{
    Debris* d;
    int x, y, w, h;

    w = e->w / 2;
    h = e->h / 2;

    for (y = 0; y <= h; y += h)
    {
        for (x = 0; x <= w; x += w)
        {
            d = malloc(sizeof(Debris));
            memset(d, 0, sizeof(Debris));
            stage.debrisTail->next = d;
            stage.debrisTail = d;

            d->x = e->x + e->w / 2;
            d->y = e->y + e->h / 2;
            d->dx = (rand() % 5) - (rand() % 5);
            d->dy = -(5 + (rand() % 12));
            d->life = FPS * 2;
            d->texture = e->texture;

            d->rect.x = x;
            d->rect.y = y;
            d->rect.w = w;
            d->rect.h = h;
        }
    }
}
static void clipPlayer()
{
    if (player != NULL)
    {
        if (player->x < 0)
        {
            player->x = 0;
        }

        if (player->y < 0)
        {
            player->y = 0;
        }

        if (player->x > SCREEN_WIDTH / 2)
        {
            player->x = SCREEN_WIDTH / 2;
        }

        if (player->y > SCREEN_HEIGHT - player->h)
        {
            player->y = SCREEN_HEIGHT - player->h;
        }
    }
}


static void fireBullet()
{
    Entity* bullet;

    bullet = malloc(sizeof(Entity));
    memset(bullet, 0, sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->x = player->x;
    bullet->y = player->y;
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->side = SIDE_PLAYER;

    bullet->texture = bulletTexture;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->y += (player->h / 2) - (bullet->h / 2);
    bullet->x += (player->w) - (bullet->w / 2);

    player->reload = 8;
}

// step through each enemy and when its alive and reload equals 0 fire a bullte
static void doEnemies()
{
    Entity* e;
    for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
    {

        if (e != player)
        {
            e->y = MIN(MAX(e->y, 0), SCREEN_HEIGHT - e->h);

            if (player != NULL && --e->reload <= 0)
            {
                fireAlienBullet(e);

                playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
            }
        }

    }
}

static void fireAlienBullet(Entity* e)
{
    Entity* bullet;

    bullet = malloc(sizeof(Entity));
    memset(bullet, 0, sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->x = e->x;
    bullet->y = e->y;
    bullet->health = 1;
    bullet->texture = alienBulletTexture;
    bullet->side = e->side;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->x += (e->w / 2) - (bullet->w / 2);
    bullet->y += (e->h / 2) - (bullet->h / 2);

    calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);

    bullet->dx *= ALIEN_BULLET_SPEED;
    bullet->dy *= ALIEN_BULLET_SPEED;

    bullet->side = SIDE_ALIEN;

    e->reload = (rand() % FPS * 2);
}


static int bulletHitFighter(Entity *b)
{
    Entity *e;

    for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
    {
        if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
        {
            b->health = 0;
            e->health = 0;

            addExplosions(e->x, e->y, 32);

            addDebris(e);

            if (e == player)
            {
                playSound(SND_PLAYER_DIE, CH_PLAYER);
            }
            else
            {
                addPointsPod(e->x + e->w / 2, e->y + e->h / 2);

                playSound(SND_ALIEN_DIE, CH_ANY);

                stage.score++;

                highscore = MAX(stage.score, highscore);
            }

            return 1;
        }
    }

    return 0;
}


static void draw()
{
    drawBackground();

    drawStarfield();

    drawPointsPods();

    drawFighters();

    drawBullets();

    drawDebris();

    drawExplosions();

    drawHud();
}



static void drawPointsPods()
{
    Entity* e;

    for (e = stage.pointsHead.next; e != NULL; e = e->next)
    {
    if (e->health > (FPS * 2) || e->health % 12 < 6)
        {

            blit(e->texture, e->x, e->y, 1);
        }
    }
}

static void drawBullets()
{
    Entity* b;

    for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
    {
        blit(b->texture, b->x, b->y, 1);
    }
}

static void drawFighters()
{
    Entity* e;

    for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
    {
        blit(e->texture, e->x, e->y, 1);
    }
}

static void drawDebris()
{
    Debris* d;

    for (d = stage.debrisHead.next ; d != NULL ; d = d->next)
    {
        blitRect(d->texture, &d->rect, d->x, d->y);
    }
}

static void drawExplosions()
{
    Explosion* e;

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

    for (e = stage.explosionHead.next ; e != NULL ; e = e->next)
    {
        SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
        SDL_SetTextureAlphaMod(explosionTexture, e->a);

        blit(explosionTexture, e->x, e->y, 1);
    }

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}


static void drawHud()
{
    drawText(10, 10, 255, 255, 255,TEXT_LEFT ,"SCORE: %03d", stage.score);

    if (stage.score > 0 && stage.score == highscore)
    {
        drawText(960, 10, 0, 255, 0,TEXT_RIGHT, "HIGH SCORE: %03d", highscore);
    }
    else
    {
        drawText(960, 10, 255, 255, 255,TEXT_RIGHT,"HIGH SCORE: %03d", highscore);
    }
}
