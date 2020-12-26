#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define Max_Terms 101

typedef struct{                             //�@��matrix�s���F��
    int row;                                
    int col;
    int value;
}term;

typedef struct{                             //�s�h��matrix
    char matrix_name[100][100];             //�̦h�s100��matrix
    int matrix_num;                         //���h��matrix
    term matrix[100][Max_Terms];            //�̦h�}100��matrix�A�@��matrix�̦h�s101�ӫD0��
}multmatrix;

multmatrix bag;

void tranpose(int32_t num ,int32_t trannum)
{
    int32_t start_row_position[bag.matrix[num][0].col];
    int32_t row_terms[bag.matrix[num][0].col];
    for(int32_t i = 0 ; i < bag.matrix[num][0].col;i++)
    {
        row_terms[i] = 0;
        start_row_position[i] = 0;
    }
    for(int32_t i = 1 ; i <= bag.matrix[num][0].value ; i++)
    {
        row_terms[bag.matrix[num][i].col] ++;
    }
    for(int32_t i = 0 ; i < bag.matrix[num][0].col ; i++)
    {
        if(i == 0)
        {
            start_row_position[i] = 1;
        }
        else
        {
            start_row_position[i] = start_row_position[i-1] + row_terms[i-1];
        }
    }
    bag.matrix[trannum][0].row = bag.matrix[num][0].col;
    bag.matrix[trannum][0].col = bag.matrix[num][0].row;
    bag.matrix[trannum][0].value = bag.matrix[num][0].value;
    for(int32_t i = 1 ; i <= bag.matrix[num][0].value ; i++)
    {
        int32_t tmp = start_row_position[bag.matrix[num][i].col]++;
        bag.matrix[trannum][tmp].col = bag.matrix[num][i].row;
        bag.matrix[trannum][tmp].row = bag.matrix[num][i].col;
        bag.matrix[trannum][tmp].value = bag.matrix[num][i].value;
    }
}

void mult(int32_t num,int32_t trannum,int32_t new)
{
    bag.matrix[new][0].row = bag.matrix[num][0].row;
    bag.matrix[new][0].col = bag.matrix[num][0].col;
    bag.matrix[new][0].value = bag.matrix[num][0].value;
    int32_t r_index = 1;
    int32_t c_index = 1;
    int32_t n_index = 1;
    int32_t r_start = 1;
    int32_t c_start = 1;
    int32_t cntrow[bag.matrix[num][0].row];
    int32_t cntcol[bag.matrix[trannum][0].row];
    int32_t indexnum = 1;
    int32_t indextran = 1;
    for(int32_t i = 0 ; i < bag.matrix[num][0].row ; i++)
    {
        cntrow[i] = 0;
        while(bag.matrix[num][indexnum].row == i)
        {
            indexnum ++;
            cntrow[i] ++;
        }
    }
    for(int32_t i = 0 ; i < bag.matrix[trannum][0].row ; i++)
    {
        cntcol[i] = 0;
        while(bag.matrix[trannum][indextran].row == i)
        {
            indextran ++;
            cntcol[i] ++;
        }
    }
    for(int32_t i = 0 ; i < bag.matrix[num][0].row ; i++)
    {
        r_index = r_start;
        c_index = 1;
        c_start = 1;
        while(c_index <= bag.matrix[trannum][0].value) 
        {
            if(r_index > bag.matrix[num][0].value || bag.matrix[num][r_index].row != bag.matrix[num][r_start].row) 
            {
                r_index = r_start;
                c_index ++;
            }
            if(c_index > bag.matrix[trannum][0].value)
                break;
            if(bag.matrix[trannum][c_index].row != bag.matrix[trannum][c_start].row) 
            {
                if(bag.matrix[new][n_index].value)
                    n_index ++;
                c_start = c_index;
                r_index = r_start;
            }
            if(bag.matrix[num][r_index].col == bag.matrix[trannum][c_index].col)
            {
                bag.matrix[new][n_index].row = bag.matrix[num][r_start].row;
                bag.matrix[new][n_index].col = bag.matrix[trannum][c_start].row;
                bag.matrix[new][n_index].value += bag.matrix[num][r_index].value*bag.matrix[trannum][c_index].value;
                r_index ++;
                if(bag.matrix[num][r_index].row != bag.matrix[num][r_start].row) {
                    r_index = r_start;
                }
                c_index ++;
            }
            else if(bag.matrix[num][r_index].col < bag.matrix[trannum][c_index].col)
            {
                r_index ++;
            }
            else if(bag.matrix[num][r_index].col > bag.matrix[trannum][c_index].col){
                c_index ++;
            }
        }
        r_start += cntrow[i];
        if(bag.matrix[new][n_index].value)
            n_index ++;
    }
    bag.matrix[new][0].value = n_index-1;
}

int main()
{
    int32_t skill = 0;
    while(skill != 7)
    {
        system("cls");
        printf("basic function:\n");
        printf("1.����L��J�@��matrix M\n");
        printf("2.�ѿù����matrix M�����e\n");
        printf("3.���wmatrix M��submatrix����s���ΦC�s���A��ܸ�submatrix�����e\n");
        printf("4.���M����m�x�}���e\n");
        printf("5.Ū�J���matrix M1��M2�A��M1��M2���[�k�A�����M1+M2�����G\n");
        printf("6.Ū�J�@��square matrix M�A�p��Mk(k���j�󵥩�2�����)�A�����Mk�����G\n");
        printf("advanced function:\n");
        printf("7.����\n");
        printf("�п�J�A�Q�n�����O:");
        scanf("%d",&skill);
        if(skill == 1)
        {
            system("cls");
            int32_t m,n,nonzero;
            char name[100];
            printf("�i���O�@�j\n�аݧA�n��J�X��matrix:");
            scanf("%d",&bag.matrix_num);
            for(int32_t i = 0 ; i < bag.matrix_num ; i++)
            {
                printf("�п�Jmatrix���W�r(���^��W�r):");
                scanf("%s",name);
                printf("�п�Jmatrix��row:");
                scanf("%d",&m);
                printf("�п�Jmatrix��column:");
                scanf("%d",&n);
                printf("�п�J�D�s���`��:");
                scanf("%d",&nonzero);
                int32_t orinmatrix[m][n];                //�}�@�Ӥ@�몺�}�C�h�s
                printf("�п�Jmatrix(�����H�Ů�j�})\n");
                for(int32_t j = 0 ; j < m ; j++)
                {
                    for(int32_t k = 0 ; k < n ; k++)
                    {
                        scanf("%d",&orinmatrix[j][k]);
                    }
                }
                int32_t checknonzero = 0;
                for(int32_t k = 0 ; k < m ; k++)
                {
                    for(int32_t j = 0 ; j < n ; j++)
                    {
                        if(orinmatrix[k][j] != 0)
                        {
                            checknonzero ++;
                        }
                    }
                }
                if(checknonzero != nonzero)
                {
                    printf("�D�s���ƶq���ŦX�A�Э��s������O�@\n");
                    bag.matrix_num = 0;
                    Sleep(2000);
                }
                //�ഫ��Sparse matrix
                else
                {
                    strcpy(bag.matrix_name[i],name);
                    int32_t cnt = 0 ;                       //�p��Sparse matrix���}�C��m
                    bag.matrix[i][cnt].row = m;
                    bag.matrix[i][cnt].col = n;
                    bag.matrix[i][cnt].value = nonzero;
                    cnt ++;
                    for(int32_t j = 0 ; j < m ; j++)
                    {
                        for(int32_t k = 0 ; k < n ; k++)
                        {
                            if(orinmatrix[j][k] != 0)
                            {
                                bag.matrix[i][cnt].row = j;
                                bag.matrix[i][cnt].col = k;
                                bag.matrix[i][cnt].value = orinmatrix[j][k];
                                cnt++;
                            }
                        }
                    }
                    // for(int32_t h = 0 ; h < cnt ; h++)        //�T�{�@�Usparse matrix
                    // {
                    //     printf("%d %d %d\n",bag.matrix[i][h].row,bag.matrix[i][h].col,bag.matrix[i][h].value);
                    // }
                    // Sleep(2000);
                }
            }
        }
        else if(skill == 2)
        {
            system("cls");
            if(bag.matrix_num == 0)
            {
                printf("�Х��e�����O�@��Jmatrix(2���۰ʪ�^����)\n");
                Sleep(2000);
            }
            else
            {
                printf("�s����matrix\n");
                for(int32_t i = 0 ; i < bag.matrix_num; i++)
                {
                    printf("%s\n",bag.matrix_name[i]);
                }
                char name[100];
                int32_t nameNum = 0;
                int32_t cnt = 1;
                int32_t check = 0;
                printf("�п�J�A�n��matrix�W��:");
                scanf("%s",&name);
                for(int32_t i = 0 ; i < bag.matrix_num ; i++)
                {
                    if(!strcmp(name,bag.matrix_name[i]))
                    {
                        nameNum = i;
                        check = 1;
                    }
                }
                if(!check)
                {
                    printf("�S���o��matrix\n");
                    Sleep(2000);
                }
                else
                {
                    int32_t cnt = 1;
                    for(int32_t i = 0 ; i < bag.matrix[nameNum][0].row ; i++)
                    {
                        for(int32_t j = 0 ; j < bag.matrix[nameNum][0].col ; j++)
                        {
                            if(bag.matrix[nameNum][cnt].row == i && bag.matrix[nameNum][cnt].col == j)
                            {
                                printf("%d ",bag.matrix[nameNum][cnt].value);
                                cnt ++;
                            }
                            else
                            {
                                printf("0 ");
                            }
                        }
                        printf("\n");
                    }
                    printf("\n\n\n");
                    printf("3���۰ʪ�^����\n");
                    Sleep(3000);
                } 
            }
        }
        else if(skill == 3)
        {
            int32_t check = 0;
            system("cls");
            printf("�s����matrix\n");
            for(int32_t i = 0 ; i < bag.matrix_num; i++)
            {
                printf("%s\n",bag.matrix_name[i]);
            }
            char name[100];
            int32_t nameNum = 0;
            printf("�п�J�A�Q�n���l���X��matrix:");
            scanf("%s",&name);
            for(int32_t i = 0 ; i < bag.matrix_num ; i++)
            {
                if(!strcmp(name,bag.matrix_name[i]))
                {
                    nameNum = i;
                    check = 1;
                }
            }
            if(!check)
            {
                printf("�S���o��matrix\n");
                Sleep(2000);
            }
            int32_t cntorin = 1;
            for(int32_t i = 0 ; i < bag.matrix[nameNum][0].row ; i++)
            {
                for(int32_t j = 0 ; j < bag.matrix[nameNum][0].col ; j++)
                {
                    if(bag.matrix[nameNum][cntorin].row == i && bag.matrix[nameNum][cntorin].col == j)
                    {
                        printf("%d ",bag.matrix[nameNum][cntorin].value);
                        cntorin ++;
                    }
                    else
                    {
                        printf("0 ");
                    }
                }
                printf("\n");
            }
            int32_t subrow,subcol;
            printf("�п�J�l���X��row��:");
            scanf("%d",&subrow);
            printf("�п�J�l���X��col��:");
            scanf("%d",&subcol);
            int32_t indexrow[subrow];
            int32_t indexcol[subcol];
            printf("�п�J�A�n���l���X��row index(0-%d):",bag.matrix[nameNum][0].row-1);
            for(int32_t i = 0 ; i < subrow ; i++)
            {
                scanf("%d",&indexrow[i]);
            }
            printf("�п�J�A�n���l���X��col index(0-%d):",bag.matrix[nameNum][0].col-1);
            for(int32_t i = 0 ; i <subcol ; i++)
            {
                scanf("%d",&indexcol[i]);
            }
            printf("submatrix:\n");
            int32_t index = 1;
            for(int32_t i = 0 ; i < subrow ; i++)
            {
                for(int32_t j = 0 ; j < subcol ; j++)
                {   
                    while(indexrow[i] > bag.matrix[nameNum][index].row)
                    {
                        index ++;
                    }
                    if(indexrow[i] == bag.matrix[nameNum][index].row)
                    {
                        while(indexcol[j] > bag.matrix[nameNum][index].col)
                        {
                            index ++;
                        }
                        if(indexcol[j] == bag.matrix[nameNum][index].col)
                        {
                            printf("%d ",bag.matrix[nameNum][index].value);
                        }
                        if(indexcol[j] < bag.matrix[nameNum][index].col)
                        {
                            printf("0 ");
                        }
                    }
                    if(indexrow[i] < bag.matrix[nameNum][index].row)
                    {
                        printf("0 ");
                    }   
                }
                printf("\n");
            }
            Sleep(3000);
        }
        else if(skill == 4)
        {
            int32_t check = 0;
            system("cls");
            printf("�s����matrix\n");
            for(int32_t i = 0 ; i < bag.matrix_num; i++)
            {
                printf("%s\n",bag.matrix_name[i]);
            }
            char name[100];
            int32_t nameNum = 0;
            int32_t tranNum = 0;
            printf("�п�J�A�Q�n��m��matrix:");
            scanf("%s",&name);
            for(int32_t i = 0 ; i < bag.matrix_num ; i++)
            {
                if(!strcmp(name,bag.matrix_name[i]))
                {
                    nameNum = i;
                    check = 1;
                }
            }
            if(!check)
            {
                printf("�S���o��matrix\n");
                Sleep(2000);
            }
            strcpy(bag.matrix_name[bag.matrix_num],"tranpose");
            strcat(bag.matrix_name[bag.matrix_num],bag.matrix_name[nameNum]);
            tranNum = bag.matrix_num;
            bag.matrix_num += 1;
            int32_t start_row_position[bag.matrix[nameNum][0].col];
            int32_t row_terms[bag.matrix[nameNum][0].col];
            for(int32_t i = 0 ; i < bag.matrix[nameNum][0].col;i++)
            {
                row_terms[i] = 0;
                start_row_position[i] = 0;
            }
            for(int32_t i = 1 ; i <= bag.matrix[nameNum][0].value ; i++)
            {
                row_terms[bag.matrix[nameNum][i].col] ++;
            }
            for(int32_t i = 0 ; i < bag.matrix[nameNum][0].col ; i++)
            {
                if(i == 0)
                {
                    start_row_position[i] = 1;
                }
                else
                {
                    start_row_position[i] = start_row_position[i-1] + row_terms[i-1];
                }
            }
            bag.matrix[tranNum][0].row = bag.matrix[nameNum][0].col;
            bag.matrix[tranNum][0].col = bag.matrix[nameNum][0].row;
            bag.matrix[tranNum][0].value = bag.matrix[nameNum][0].value;
            for(int32_t i = 1 ; i <= bag.matrix[nameNum][0].value ; i++)
            {
                int32_t tmp = start_row_position[bag.matrix[nameNum][i].col]++;
                bag.matrix[tranNum][tmp].col = bag.matrix[nameNum][i].row;
                bag.matrix[tranNum][tmp].row = bag.matrix[nameNum][i].col;
                bag.matrix[tranNum][tmp].value = bag.matrix[nameNum][i].value;
            }
            printf("%s\n",bag.matrix_name[nameNum]);
            int32_t cntorin = 1;
            for(int32_t i = 0 ; i < bag.matrix[nameNum][0].row ; i++)
            {
                for(int32_t j = 0 ; j < bag.matrix[nameNum][0].col ; j++)
                {
                    if(bag.matrix[nameNum][cntorin].row == i && bag.matrix[nameNum][cntorin].col == j)
                    {
                        printf("%d ",bag.matrix[nameNum][cntorin].value);
                        cntorin ++;
                    }
                    else
                    {
                        printf("0 ");
                    }
                }
                printf("\n");
            }
            printf("%s\n",bag.matrix_name[bag.matrix_num-1]);
            int32_t cnt = 1;
            for(int32_t i = 0 ; i < bag.matrix[tranNum][0].row ; i++)
            {
                for(int32_t j = 0 ; j < bag.matrix[tranNum][0].col ; j++)
                {
                    if(bag.matrix[tranNum][cnt].row == i && bag.matrix[tranNum][cnt].col == j)
                    {
                        printf("%d ",bag.matrix[tranNum][cnt].value);
                        cnt ++;
                    }
                    else
                    {
                        printf("0 ");
                    }
                }
                printf("\n");
            }
            printf("\n\n\n");
            printf("3���۰ʪ�^����\n");
            Sleep(3000);
        }
        else if(skill == 5)
        {
            int32_t check = 0;
            system("cls");
            printf("�s����matrix\n");
            for(int32_t i = 0 ; i < bag.matrix_num; i++)
            {
                printf("%s\n",bag.matrix_name[i]);
            }
            char M1name[100];
            char M2name[100];
            int32_t M1Num,M2Num;
            printf("�п�J�A�Q�n��M1:");
            scanf("%s",M1name);
            printf("�п�J�A�Q�n��M2:");
            scanf("%s",M2name);
            for(int32_t i = 0 ; i < bag.matrix_num ; i++)
            {
                if(!strcmp(M1name,bag.matrix_name[i]))
                {
                    M1Num = i;
                    check = 1;
                }
                if(!strcmp(M2name,bag.matrix_name[i]))
                {
                    M2Num = i;
                    check = 1;
                }
            }
            if(!check)
            {
                printf("�S���o��matrix\n");
                Sleep(2000);
            }
            if(bag.matrix[M1Num][0].row != bag.matrix[M2Num][0].row || bag.matrix[M1Num][0].col != bag.matrix[M2Num][0].col)
            {
                printf("�o���matrix��row��col���P�A����@�[�k.\n");
                printf("�Э��s������O��");
                printf("\n\n\n3���۰ʪ�^����");
                Sleep(3000);
            }
            else
            {
                system("cls");
                printf("M1\n");
                int32_t cntorin = 1;
                for(int32_t i = 0 ; i < bag.matrix[M1Num][0].row ; i++)
                {
                    for(int32_t j = 0 ; j < bag.matrix[M1Num][0].col ; j++)
                    {
                        if(bag.matrix[M1Num][cntorin].row == i && bag.matrix[M1Num][cntorin].col == j)
                        {
                            printf("%d ",bag.matrix[M1Num][cntorin].value);
                            cntorin ++;
                        }
                        else
                        {
                            printf("0 ");
                        }
                    }
                    printf("\n");
                }
                printf("M2\n");
                cntorin = 1;
                for(int32_t i = 0 ; i < bag.matrix[M2Num][0].row ; i++)
                {
                    for(int32_t j = 0 ; j < bag.matrix[M2Num][0].col ; j++)
                    {
                        if(bag.matrix[M2Num][cntorin].row == i && bag.matrix[M2Num][cntorin].col == j)
                        {
                            printf("%d ",bag.matrix[M2Num][cntorin].value);
                            cntorin ++;
                        }
                        else
                        {
                            printf("0 ");
                        }
                    }
                    printf("\n");
                }
                printf("anwer:\n");
                int32_t cntM1 = 1;
                int32_t cntM2 = 1;
                for(int32_t i = 0 ; i < bag.matrix[M1Num][0].row ; i++)
                {
                    for(int32_t j = 0 ; j < bag.matrix[M1Num][0].col ; j++)
                    {
                        int32_t check =0;
                        if(bag.matrix[M1Num][cntM1].row == i && bag.matrix[M1Num][cntM1].col == j)
                        {
                            if(bag.matrix[M2Num][cntM2].row == i && bag.matrix[M2Num][cntM2].col == j)
                            {
                                printf("%d ",bag.matrix[M1Num][cntM1].value + bag.matrix[M2Num][cntM2].value);
                                cntM1 ++;
                                cntM2 ++;
                                check = 1;
                            }
                            else
                            {
                                printf("%d ",bag.matrix[M1Num][cntM1].value);
                                cntM1 ++;
                                check = 1;
                            }
                        }
                        else if(bag.matrix[M2Num][cntM2].row == i && bag.matrix[M2Num][cntM2].col == j)
                        {
                            printf("%d ",bag.matrix[M2Num][cntM2].value);
                            cntM2 ++;
                            check = 1;
                        }
                        if(!check)
                        {
                            printf("0 ");
                        }
                    }
                    printf("\n");
                }
                Sleep(5000);
            }   
        }
        else if(skill == 6)
        {
            int32_t check = 0;
            system("cls");
            printf("�s����matrix\n");
            for(int32_t i = 0 ; i < bag.matrix_num; i++)
            {
                printf("%s\n",bag.matrix_name[i]);
            }
            char name[100];
            printf("�п�J�A�Q�n��matrix:");
            scanf("%s",name);
            int32_t num = 0;
            for(int32_t i = 0 ; i < bag.matrix_num ; i++)
            {
                if(!strcmp(name,bag.matrix_name[i]))
                {
                    num = i;
                    check = 1;
                }
            }
            
            if(!check)
            {
                printf("�S���o��matrix\n");
                Sleep(2000);
            }
            if(bag.matrix[num][0].row != bag.matrix[num][0].col)
            {
                printf("�o���O�@��square matrix.");
                Sleep(3000);
            }
            else
            {
                int32_t k = 0;
                printf("�п�J�A�n��k��(k>=2):");
                scanf("%d",&k);
                if(k < 2)
                {
                    printf("k >= 2\n");
                }
                else
                {
                    int32_t bin[1000];            //��k��2�i��A�s�i�hbin�̭�
                    int32_t cnt = 0;
                    while(k)
                    {
                        bin[cnt]=k%2;
                        k /= 2;
                        cnt ++;
                    }
                    int32_t tranNum = bag.matrix_num;             //transpose matrix
                    bag.matrix_num ++;
                    int32_t baseNum = bag.matrix_num;                                         //�n�sans��matrix
                    bag.matrix_num ++;
                    int32_t tmpNum = bag.matrix_num;
                    bag.matrix_num ++;
                    int32_t tempNum = bag.matrix_num;
                    bag.matrix_num ++;
                    for(int32_t i = 0 ; i <= bag.matrix[num][0].value ; i++)
                    {
                        bag.matrix[baseNum][i].row = bag.matrix[num][i].row;
                        bag.matrix[baseNum][i].col = bag.matrix[num][i].col;
                        bag.matrix[baseNum][i].value = bag.matrix[num][i].value;
                    }
                    int32_t ansNum = bag.matrix_num;
                    bag.matrix_num ++;
                    bag.matrix[ansNum][0].row = bag.matrix[num][0].row;
                    bag.matrix[ansNum][0].col = bag.matrix[num][0].col;
                    bag.matrix[ansNum][0].value = bag.matrix[num][0].value;
                    for(int32_t i = 0 ; i < bag.matrix[num][0].row ; i++)
                    {
                        bag.matrix[ansNum][i+1].row = i;
                        bag.matrix[ansNum][i+1].col = i;
                        bag.matrix[ansNum][i+1].value = 1;
                    }
                    for(int32_t i = 0 ; i < cnt ; i++)
                    {
                        if(i != 0)
                        {
                            tranpose(baseNum,tranNum);
                            mult(baseNum,tranNum,tmpNum);
                            for(int32_t i = 1 ; i <= bag.matrix[tmpNum][0].value ; i++)
                            {
                                bag.matrix[baseNum][i].row = 0;
                                bag.matrix[baseNum][i].col = 0;
                                bag.matrix[baseNum][i].value = 0;
                            }
                            for(int32_t i = 0 ; i <= bag.matrix[tmpNum][0].value ; i++)
                            {
                                bag.matrix[baseNum][i].row = bag.matrix[tmpNum][i].row;
                                bag.matrix[baseNum][i].col = bag.matrix[tmpNum][i].col;
                                bag.matrix[baseNum][i].value = bag.matrix[tmpNum][i].value;
                            }
                        }
                        if(bin[i] == 1)
                        {
                            tranpose(baseNum,tranNum);
                            for(int32_t i = 1 ; i <= bag.matrix[tempNum][0].value ; i++)
                            {
                                bag.matrix[tempNum][i].row = 0;
                                bag.matrix[tempNum][i].col = 0;
                                bag.matrix[tempNum][i].value = 0;
                            }
                            mult(ansNum,tranNum,tempNum);
                            for(int32_t i = 0 ; i <= bag.matrix[tempNum][0].value ; i++)
                            {
                                bag.matrix[ansNum][i].row = bag.matrix[tempNum][i].row;
                                bag.matrix[ansNum][i].col = bag.matrix[tempNum][i].col;
                                bag.matrix[ansNum][i].value = bag.matrix[tempNum][i].value;
                            }
                        }
                    }
                    cnt = 1;                                                                 //��ans��matrix�L�X��
                    for(int32_t i = 0 ; i < bag.matrix[ansNum][0].row ; i++)
                    {
                        for(int32_t j = 0 ; j < bag.matrix[ansNum][0].col ; j++)
                        {
                            if(bag.matrix[ansNum][cnt].row == i && bag.matrix[ansNum][cnt].col == j)
                            {
                                printf("%d ",bag.matrix[ansNum][cnt].value);
                                cnt ++;
                            }
                            else
                            {
                                printf("0 ");
                            }
                        }
                        printf("\n");
                    }
                    Sleep(3000);
                }
            }
        }
    }
    return 0;
}

/*
3 0 0 
0 2 0
0 0 1

-256 0 0 0 0 0 0 0 0 255
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
255 0 0 0 0 0 0 0 0 -256

4 7 11 
8 2 -3

0 0 1
1 0 1
0 1 0

4096 0 0 0 0 0 0 0 0 -1
0 2048 0 0 0 0 0 0 -1 0
0 0 1024 0 0 0 0 -1 0 0 
0 0 0 512 0 0 -1 0 0 0
0 0 0 0 256 -1 0 0 0 0
0 0 0 0 1 -256 0 0 0 0
0 0 0 1 0 0 -128 0 0 0
0 0 1 0 0 0 0 -64 0 0
0 1 0 0 0 0 0 0 -32 0
1 0 0 0 0 0 0 0 0 -162
*/