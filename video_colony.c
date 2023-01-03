#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct comment
{
    char cmnt[100];
    struct comment *next;
};
struct node
{
    int data;
    int like;
    char description[100];
    struct node *right, *left;
    struct comment *cmnt;
};
void upload(struct node **videos, int x);
struct node *search(struct node **videos, int x);
void play(struct node **videos, struct node **history,int x);
void comment(struct node **videos, int x);
void like(struct node **videos,struct node **liked , int x);
void display(struct node *videos);
void vcmnts(struct comment *cmt);
void delete(struct node **videos, int x);
void delete(struct node **videos, int x)
{
    struct node *pres, *prev, *q,*p;
    pres = (*videos);
    prev = NULL;
    if ((*videos) == NULL)
    {
        printf("No videos present over here\n");
    }
    else
    {
        while (pres->data != x && pres != NULL)
        {
            prev = pres;
            if (x < pres->data)
                pres = pres->left;
            else
                pres = pres->right;
        }
        if (pres == NULL)
        {
            printf("No node present here of that id\n");
        }
        else
        {
            if (pres->left == NULL && pres->right == NULL)
            {
                if (prev == NULL)
                {
                    free(pres);
                }
                else
                {
                    if (prev->left == pres)
                        prev->left = NULL;
                    else if (prev->right == pres)
                        prev->right = NULL;
                    free(pres);
                }
            }
            else if (pres->left == NULL || pres->right == NULL)
            {
                if (prev == NULL)
                {
                    if(pres->right==NULL)
                    {
                        (*videos)=pres->left;
                    }
                    else{
                        (*videos)=pres->right;
                    }
                    free(pres);
                }
                else
                {
                    if (pres->left == NULL)
                    {
                        if (prev->left == pres)
                            prev->left = pres->right;
                        else
                            prev->right = pres->right;
                    }
                    else if (pres->right == NULL)
                    {
                        if (prev->left == pres)
                            prev->left = pres->left;
                        else
                            prev->right = pres->left;
                    }
                    free(pres);
                }
            }
            else
            {
                q = pres->right;
                while (q->left != NULL)
                {
                    q = q->left;
                }
                pres = q;
                free(q);
            }
        }
    }
}

void vcmnts(struct comment *cmt)
{
    struct comment *q;
    q = cmt;
    if (cmt == NULL)
    {
        printf("No comments yet\n");
    }
    else
    {
        printf("The comments of selected video are\n");
        while (q != NULL)
        {
            printf("%s\n", q->cmnt);
            q = q->next;
        }
    }
}
void display(struct node *videos)
{
    if (videos != NULL)
    {
        display(videos->left);
        printf("%d\t", videos->data);
        display(videos->right);
    }
}
void like(struct node **videos,struct node **liked ,int x)
{
    struct node *q, *qr;
    q = search(videos, x);
    if (q != NULL)
    {
        (q->like)++;
        printf("Total like are %d\n", q->like);
        upload(liked,x);
    }
    else
    {
        printf("Video not found\n");
    }
}
void comment(struct node **videos, int x)
{
    struct node *temp;
    temp = search(videos, x);
    if (temp == NULL)
    {
        printf("Video not found\n");
    }
    else
    {
        struct comment *c, *prev, *q;
        char s[100];
        q = temp->cmnt;
        c = (struct comment *)malloc(sizeof(struct comment));
        printf("Write a comment : ");
        scanf("%s", c->cmnt);
        prev = NULL;
        if (temp->cmnt == NULL)
        {
            temp->cmnt = c;
            temp->cmnt->next = NULL;
        }
        else
        {
            while (q != NULL)
            {
                prev = q;
                q = q->next;
            }
            prev->next = c;
            q=c;
            q->next=NULL;
        }
        vcmnts(temp->cmnt);
    }
}
struct node *search(struct node **videos, int x)
{
    struct node *pres;
    pres = (*videos);
    while (pres != NULL && pres->data != x)
    {
        if (x < pres->data)
        {
            pres = pres->left;
        }
        else
        {
            pres = pres->right;
        }
    }
    return pres;
}
void upload(struct node **videos, int x)
{
    struct node *prev, *temp, *cur;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = x;
    temp->like = 0;
    temp->cmnt = NULL;
    temp->left = temp->right = NULL;
    if ((*videos) == NULL)
    {
        (*videos) = temp;
    }
    else
    {
        prev = NULL;
        cur = *videos;
        while (cur != NULL)
        {
            prev = cur;
            if (x < (cur->data))
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        if (x < (prev->data))
        {
            prev->left = temp;
        }
        else
        {
            prev->right = temp;
        }
    }
}
void play(struct node **videos,struct node **history, int x)
{
    struct node *q;
    q = search(videos, x);
    if (q != NULL)
    {
        printf("\nPlaying %d\n", q->data);
        upload(history,x);
    }
    else
    {
        printf("\nSong not found\n");
    }
}
int main()
{
    struct node *videos, *q, *saved,*liked,*history;
    videos = NULL;
    saved = NULL;
    history=NULL;
    liked=NULL;
    int x, ch;
    do
    {
        printf("\n0)Exit\n1)Upload video\n2)Search and play video\n3)Comment on video\n4)Like video\n5)Save video\n6)View saved videos\n7)Delete video\n8)Unsave video\n9)Display videos\n10)View Liked videos\n11)View watch history\n12)Clear history\n\nEnter your choice : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter video id : ");
            scanf("%d", &x);
            upload(&videos, x);
            break;
        case 2:
            printf("Enter video id to search : ");
            scanf("%d", &x);
            play(&videos, &history,x);
            break;
        case 3:
            printf("Enter video id : ");
            scanf("%d", &x);
            comment(&videos, x);
            break;
        case 4:
            printf("Enter video id : ");
            scanf("%d", &x);
            like(&videos, &liked,x);
            break;
        case 5:
            printf("Enter video id : ");
            scanf("%d", &x);
            q = search(&videos, x);
            if (q == NULL)
            {
                printf("Video not found\n");
            }
            else
            {
                upload(&saved, x);
            }
            break;
        case 6:
            if (saved != NULL)
            {
                printf("\n");
                display(saved);
                printf("\n");
            }
            else
            {
                printf("\nNo saved videos present at the moment\n");
            }
            break;
        case 7:
            printf("Enter video id : ");
            scanf("%d", &x);
            delete (&videos, x);
            break;
        case 8:
            printf("Enter video id : ");
            scanf("%d", &x);
            delete (&saved, x);
            break;
        case 9:
            if (videos != NULL)
            {
                printf("\n");
                display(videos);
                printf("\n");
            }
            break;
        case 10:
            if (liked != NULL)
            {
                printf("\n");
                display(liked);
                printf("\n");
            }
            break;
        case 11:
            if (history == NULL)
            {
                printf("\nThe history is blank\n");
            }
            else
            {
                printf("\n");
                display(history);
                printf("\n");
            }
            break;
        case 12:
            history=NULL;
            break;
        }
    } while (ch != 0);

    return 0;
}