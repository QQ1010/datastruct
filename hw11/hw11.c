#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct road
{
    int32_t key;
    int32_t r_govenment;
    struct road *link;
}road;

int choose (int32_t *distance, int32_t n, short int *found)
{   /* find the smallest distance not yet checked */
    int32_t min, minpos;
    min = 100000;
    minpos = -1;
    for (int32_t i = 0; i < n ; i++)
        if(distance[i] < min && !found[i])
        {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

int main()
{
    int32_t v,e,c;
    scanf("%d %d %d",&v,&e,&c);
    // printf("%d %d %d\n",v,e,c);
    int32_t city[v+1];
    for(int32_t i = 1 ; i < v+1 ; i++)
    {
        scanf("%d",&city[i]);
        // printf("%d\n",city[i]);
    }
    struct road cost[101][101];            //original road
    for(int32_t i = 0 ; i < v+1 ; i++)
    {
        for(int32_t j = 0 ; j < v+1 ; j++)
        {
            if(i == j)
                cost[i][j].key = 0;
            else if(i != j)
                cost[i][j].key = 10000;
            cost[i][j].r_govenment = -1;
            cost[i][j].link = NULL;
        }
    }
    // for(int32_t i = 0 ; i < v+1 ; i++)
    // {
    //     for(int32_t j = 0 ; j < v+1 ; j++)
    //     {
    //         if(cost[i][j].link == NULL)
    //             printf("%d ",cost[i][j].key);
    //         else if(cost[i][j].link != NULL)
    //         {    
    //             struct road *w;
    //             w = &cost[i][j];
    //             for(w ; w != NULL ; w = w->link)
    //             printf("%d ",w->key);
    //         }
    //     }
    //     printf("\n");
    // }
    for(int32_t i = 0 ; i < e ; i++)
    {
        int32_t tmp1,tmp2,tmp3,tmp4;
        scanf("%d %d %d %d",&tmp1,&tmp2,&tmp3,&tmp4);
        if(cost[tmp1][tmp2].key == 10000)
        {
            cost[tmp1][tmp2].key = tmp3;
            cost[tmp1][tmp2].r_govenment = tmp4;
            cost[tmp2][tmp1].key = tmp3;
            cost[tmp2][tmp1].r_govenment = tmp4;
        }
        else if(cost[tmp1][tmp2].key != 10000)
        {
            struct road w;
            w.key = tmp3;
            w.r_govenment = tmp4;
            w.link = NULL;
            cost[tmp1][tmp2].link = &w;
            cost[tmp2][tmp1].link = &w;
        }
    }
    // for(int32_t i = 0 ; i < v+1 ; i++)
    // {
    //     for(int32_t j = 0 ; j < v+1 ; j++)
    //     {
    //         if(cost[i][j].link == NULL)
    //             printf("%d ",cost[i][j].key);
    //         else if(cost[i][j].link != NULL)
    //         {    
    //             struct road *w;
    //             w = &cost[i][j];
    //             for(w ; w != NULL ; w = w->link)
    //             printf("%d ",w->key);
    //         }
    //     }
    //     printf("\n");
    // }
    int32_t money;
    scanf("%d",&money);
    int32_t route_num = 0;
    scanf("%d",&route_num);
    int32_t route[route_num];
    for(int32_t i = 0 ; i < route_num ; i++)
    {
        scanf("%d",&route[i]);
    }
    // printf("\n");
    int32_t walk[c];
    int32_t cntwalk = 0;
    int32_t totaldist = 0;
    for(int32_t i = 0 ; i < route_num-1 ; i++)
    {
        walk[cntwalk++] = route[i];
        short int found[v+1];
        int32_t dist[v+1];
        int32_t u;
        for(int32_t j = 0 ; j < v+1 ; j++)
        {
            found[j] = false;
            if(cost[route[i]][j].link == NULL)
            {
                if(city[route[i]] == cost[route[i]][j].r_govenment)
                    dist[j] = cost[route[i]][j].key;
                else if(cost[route[i]][j].r_govenment != -1 && city[route[i]] != cost[route[i]][j].r_govenment)
                    dist[j] = cost[route[i]][j].key*money;
                else if(cost[route[i]][j].r_govenment == -1)
                    dist[j] = cost[route[i]][j].key;
            }
            else if(cost[route[i]][j].link != NULL)
            {
                int32_t tmp[2000];
                int32_t cnt = 0;
                struct road *w = &cost[route[i]][j];
                for( w ; w != NULL ; w = w->link)
                {
                    if(city[route[i]] == w->r_govenment)
                        tmp[cnt] = w->key;
                    else if(w->r_govenment != -1 && city[route[i]] != w->r_govenment)
                        tmp[cnt] = w->key*money;
                    else if(w->r_govenment == -1)
                        tmp[cnt] = w->key;
                    cnt ++;
                }
                int32_t min = tmp[0];
                for(int32_t k = 0 ; k < cnt ; k++)
                {
                    if(min > tmp[k])
                        min = tmp[k];
                }
                dist[j] = min;
            }
            // printf("dist[%d] = %d ",j,dist[j]);
        }
        // printf("\n");
        found[route[i]] = true;
        dist[route[i]] = 0;
        for(int32_t j = 0 ; j < v-1 ; j++)
        {
            u = choose(dist,v+1,found);
            found[u] = true;
            for(int32_t w = 1 ; w < v+1 ; w++)
            {
                // printf("%d ",dist[w]);
                if(!found[w])
                {
                    if(w == route[i+1])
                    {
                        if(cost[u][w].link == NULL)
                        {
                            if(cost[u][w].r_govenment == city[route[i]])
                            {
                                if(dist[u]+cost[u][w].key < dist[w])
                                {
                                    dist[w] = dist[u] + cost[u][w].key;
                                    walk[cntwalk++] =u; 
                                }
                            }
                            else if(cost[u][w].r_govenment != city[route[i]])
                            {
                                if(dist[u]+(cost[u][w].key*money) < dist[w])
                                {
                                    dist[w] = dist[u] + (cost[u][w].key*money);
                                    walk[cntwalk++] =u;
                                }
                            }
                        }
                        else if(cost[u][w].link != NULL)
                        {
                            struct road *t = &cost[u][w];
                            int32_t tmp[2000];
                            int32_t cnt = 0;
                            for( t ; t != NULL ; t = t->link)
                            {
                                if(t->r_govenment == city[route[i]])
                                {
                                    if(dist[u] + t->key < dist[w])
                                    {
                                        tmp[cnt++] = dist[u] + t->key;
                                        walk[cntwalk++] = u;
                                    }
                                }
                                else if(t->r_govenment != city[route[i]])
                                {
                                    if(dist[u]+(t->key*money) < dist[w])
                                    {
                                        tmp[cnt++] = dist[u] + (t->key*money);
                                        // printf("tmp[%d] = %d",cnt,tmp[cnt]);
                                        walk[cntwalk++] = u;
                                    }
                                }
                            }
                            int32_t min = tmp[0];
                            for(int32_t k = 0 ; k < cnt ; k++)
                            {
                                if(min > tmp[k])
                                    min = tmp[k];
                                // printf("tmp[%d] = %d ",k,tmp[k]);
                            }
                            if(cnt > 0)
                                dist[w] = min;
                        }
                    }
                    else
                    {
                        if(cost[u][w].link == NULL)
                        {
                            if(cost[u][w].r_govenment == city[route[i]])
                            {
                                if(dist[u]+cost[u][w].key < dist[w])
                                    dist[w] = dist[u] + cost[u][w].key;
                            }
                            else if(cost[u][w].r_govenment != city[route[i]])
                            {
                                if(dist[u]+(cost[u][w].key*money) < dist[w])
                                    dist[w] = dist[u] + (cost[u][w].key*money);
                            }
                        }
                        else if(cost[u][w].link != NULL)
                        {
                            struct road *t = &cost[u][w];
                            int32_t tmp[2000];
                            int32_t cnt = 0;
                            for( t ; t != NULL ; t = t->link)
                            {
                                if(t->r_govenment == city[route[i]])
                                {
                                    if(dist[u] + t->key < dist[w])
                                        tmp[cnt++] = dist[u] + t->key;
                                }
                                else if(t->r_govenment != city[route[i]])
                                {
                                    if(dist[u]+(t->key*money) < dist[w])
                                        tmp[cnt++] = dist[u] + (t->key*money);
                                }
                            }
                            int32_t min = tmp[0];
                            for(int32_t k = 0 ; k < cnt ; k++)
                            {
                                if(min > tmp[k])
                                    min = tmp[k];
                            }
                            if(cnt > 0)
                                dist[w] = min;
                        }
                    }
                }
            }
            // printf("\n");
        }
        // for(int32_t j = 0 ; j < v+1 ; j++)
        // {
        //     printf("dist[%d] = %d ",j,dist[j]);
        // }
        // printf("\n");
        totaldist += dist[route[i+1]];
        walk[cntwalk] = route[i+1];
        printf("%d\n",totaldist);
        for(int32_t k = 0 ; k < cntwalk ; k++)
        {
            printf("%d -> %d ",walk[k],walk[k+1]);
        }
    }
}