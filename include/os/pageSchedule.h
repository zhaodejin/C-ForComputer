#include "utils/utils.h"
#define MAXAREA 20
#define TATOLNUM 320 
static int subsript = 0;
static int instruction[TATOLNUM];
static int page[TATOLNUM];
static int memory[MAXAREA];
static void createInsruction(int,int);
static void replaceArithmatic(int,int);
static void FIFO(int,int,int*);
static void LRU(int,int,int*);
static void OPT(int,int,int*);
static void LFU(int,int,int*);
static int schedule();
static void createInsruction(int begin, int end)
{
    int m0, m1, m2;
    for (; subsript < TATOLNUM - 3;)
    {
        m0 = (rand() % (end - begin)) + begin;
        instruction[subsript] = m0;
        page[subsript] = m0 / 10;
        subsript++;
        instruction[subsript] = m0 + 1;
        page[subsript] = (m0 + 1) / 10;
        subsript++;
        m1 = rand() % (m0 - begin) + begin;
        instruction[subsript] = m1;
        page[subsript] = m1 / 10;
        subsript++;
        instruction[subsript] = m1 + 1;
        page[subsript] = (m1 + 1) / 10;
        subsript++;
        m2 = rand() % (end - m0) + m0;
        instruction[subsript] = m2;
        page[subsript] = m2 / 10;
        subsript++;
    }
}
static void replaceArithmatic(int frameNmum, int mode)
{
    int i, j, k;
    int memoryPointer = 0;
    int full = 0;
    int flag = -1;
    int overflow = 0;
    for (int i = 0; i < frameNmum; ++i)
    {
        memory[i] = -1;
    }
    for (int i = 0; i < TATOLNUM; i++)
    {
        for (int j = 0; i < frameNmum; i++)
        {
            if (memory[j] == -1) /* code */
            {
                if (j == frameNmum - 1)
                    full = 1;

                cout << "interrupt" << endl;
                memory[j] = page[i];
                overflow++;
                break;
            }
            if (full == 1 && memory[j] == page[i])
            {
                cout << "\nOK\n";
                break;
            }
        }
        if (j == frameNmum)
        {
            if (mode == 0)
            {
                OPT(i, frameNmum, &overflow);
            }
            else if (mode == 1)
            {
                FIFO(i, frameNmum, &overflow);
            }
            else if (mode == 2)
            {
                LRU(i, frameNmum, &overflow);
            }
            else
            {
                LFU(i, frameNmum, &overflow);
            }
        }
        printf("step %3d:   request page:%3d request:", i, page[i]);
        for (j = 0; j < frameNmum; j++)
        {
            printf("|%2d|   ", memory[j]); /* code */
        }
        printf("\n");

        /* code */
    }
    printf("\nInterruption rate is %f\n", overflow * 1.0 / TATOLNUM);
}
void OPT(int station, int frameNmum, int *overflow)
{
    int j, k;
    int flag = -1;
    printf("\nInterruption!(OPT)\n");
    for (j = station; j < TATOLNUM; j++)
    {
        for (k = 0; k < frameNmum; k++)
        {
            if (memory[flag] == page[j]) /* code */
            {
                flag = k;
                break;
            }
        }
    }
    if (flag != -1)
    {
        memory[flag] = page[station];
    }
    else
    {
        memory[0] = page[station];
    }
    *overflow += 1;
}

static void FIFO(int station, int frameNmum, int *overflow)
{
    printf("\nInterrupt!(FIFO)\n");
    int m = *overflow % frameNmum;
    memory[m] = page[station];
    *overflow += 1;
}

void LRU(int station, int frameNmum, int *overflow)
{
    printf("\nInterrupt!(FIFO)\n");
    int i, j;
    int flag = -1;
    for (i = station; i >= 0; i--)
    {
        for (j = 0; j < frameNmum; j++)
        {
            if (memory[j] == page[i])
            {
                flag = j;
                break;
            } /* code */
        }

        /* code */
    }
    if (flag == -1)
    {
        memory[0] = page[station];
    }
    else
    {
        memory[flag] = page[station];
    }
    *overflow += 1;
}

static void LFU(int station, int frameNmum, int *overflow)
{
    printf("\nInterrupt!(LFU)\n");
    int times[MAXAREA] = {0};
    int max;
    int flag = 0;
    int i, j;
    for (i = 0; i >= 0; i--)
    {
        for (j = 0; j < frameNmum; j++)
        {
            if (memory[j] == page[i])
            {
                times[j]++;
                break;
            }
        }
        /* code */
    }
    max = times[0];
    for (j = 0; j < frameNmum; j++)
    {
        if (times[j] > max)
        {
            flag = j;
            max = times[j];
        }
    }
    memory[flag] = page[station];
    *overflow += 1;
}
static int schedule()
{
    int i;
    int mode;
    int frameNum = -1;
    logger.info("rewrewrrewrewewrwe");
    srand((unsigned)time(NULL));
   
    createInsruction(0, TATOLNUM);
    printf("The semgment and the page:\n");
    for (i = 1; i < TATOLNUM; i++)
    {
        /* code */ printf("%3d.Semgment:%4d  Page:%3d    |\t", i, instruction[i - 1], page[i - 1]);
        if (i % 4 == 0)
            printf("\n");
    }
    cout << "\n============================================================\n";
    cout << "*\n";
    cout << "*mode:   (0:OPT\t1:FIFO\t2:LRU\t3:LRF\t-1:exit)\n";
    cout << "frameNum: (1~20)\n*\n";
    cout << "  ==============================================================\n";
    cout << "please input the frameNum:\n";
    scanf("%d", &frameNum);
    while (frameNum > 20 || frameNum <= 0)
    {
        /* code */ printf("Input error!Please try again!\n");
        scanf("%d", &frameNum);
    }
    while (mode != -1)
    {
        /* code */ printf("Please input the mode:\n");
        scanf("%d", &mode);
        switch (mode)
        {
        case -1:
            printf("exit!\n");
            break;
        case 0:
            printf("===================run the OPT================\n");
            replaceArithmatic(frameNum, 0);
            break;
        case 1:
            printf("===================run the FIFO================\n");
            replaceArithmatic(frameNum, 1);
            break;
        case 2:
            printf("===================run the FIFO================\n");
            replaceArithmatic(frameNum, 2);
            break;
        case 3:
            printf("===================run the FIFO================\n");
            replaceArithmatic(frameNum, 3);
            break;
        default:
            cout << "Input error!\n";
            break;
        }
    }
    return 0;
}