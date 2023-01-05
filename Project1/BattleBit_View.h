#pragma once
#include<iostream>
#include"define.h"
//#include"BattleBit_Control.h"
#include"BattleBit_Model.h"
#include<thread>
using namespace std;


class BattleBit_View {
public:
    string name;
    //Soldier* empty1;
   // Soldier* block;
   // Soldier* atk_base;
   // Soldier* def_base;
   // Soldier*** s;
    //BattleBit_Control battle_control;
   BattleBit_View(){}
    //BattleBit_View(Soldier***&s1, Soldier*& block1, Soldier*& empty11, Soldier*& atk_base1, Soldier*& def_base1) {
      //  s = s1;
     //   empty1 = empty11;
     //   block = block1;
     //  atk_base = atk_base1;
      //  def_base = def_base1;
      //  s = Soldier::getinstance();
        //battle_control = battle_control1;
    //}

    char hand_mode() {
       // getchar();
        //cout << "输入 Enter" << endl;
        return getchar();
    }
    int select_mode() {
        int watch_mode;
        cout << "请选择观看战斗模式：0--关闭  1--自动  2--手动" << endl;
        cin >> watch_mode;
        return watch_mode;
    }

    void update(int base_hp, int side) {
        if (side == 1) {
            cout << "进攻方基地正在遭受攻击!" << endl;
            cout << "进攻方基地血量：" << base_hp << endl;
        }
        if (side == 2) {
            cout << "防守方基地正在遭受攻击!" << endl;
            cout << "防守方基地血量：" << base_hp << endl;
        }
    }



    //打印士兵信息表格
    void print_init_list()
    {
        printf(YELLOW"-------------------------------------------------------------" NONE);
        cout << endl;
        printf(YELLOW"■■■欢迎来到BattleBit——一款基于沙盘回合制的战旗游戏■■■" NONE);
        cout << endl;
        printf(YELLOW"-------------------------------------------------------------" NONE);
        cout << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|类型  |符号 |造价|攻击力|暴击率|防御力|血量|攻击范围|移动距离| " << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|弓箭手 |B    |100 |15    |10%   |1     |90  |1～3    |1       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|步兵   |F    |75  |15    |5%    |3     |100 |1       |1       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|骑兵   |K    |125 |18    |8%    |5     |120 |1       |3       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|英雄   |S    |0   |25    |15%   |10    |150 |1       |1       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|基地   |H    |0   |5     |15%   |1     |200 |3       |0       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "兵种相克关系：弓箭手克步兵，步兵克骑兵，骑兵克弓箭手,相克会造成1.5倍伤害" << endl;
    }

    //打印战斗地图
    void print_war_field(Soldier***& s, Soldier*& block, int row, int col)
    {
        cout << "----------------------------------------" << endl;
        int i = 0, j = 0;

      //#pragma omp parallel for 
        for ( i = 0; i < row; i++)
        {
            for (j = 0; j < col; ++j)
            {
                if (s[i][j]->type == bowman)
                {
                    if (s[i][j]->side == def)
                        printf(GREEN"B" NONE);
                    else if (s[i][j]->side == atk)
                        printf(RED"B" NONE);
                }
                else if (s[i][j]->type == footman)
                {
                    if (s[i][j]->side == def)
                        printf(GREEN"F" NONE);
                    else if (s[i][j]->side == atk)
                        printf(RED"F" NONE);
                }
                else if (s[i][j]->type == knight)
                {
                    if (s[i][j]->side == def)
                        printf(GREEN"K" NONE);
                    else if (s[i][j]->side == atk)
                        printf(RED"K" NONE);
                }
                else if (s[i][j]->type == base)
                {
                    if (s[i][j]->side == def)
                        printf(GREEN"H" NONE);
                    else if (s[i][j]->side == atk)
                        printf(RED"H" NONE);
                }
                else if (s[i][j] == block) {
                    printf(NONE"*" NONE);
                }
                else if (s[i][j]->type == normal)
                    cout << " ";
            }
            cout << endl;

        }
        cout << "----------------------------------------" << endl;

    }

    void print_war_state(Soldier***&s,int row, int col,Soldier*&def_base, Soldier*& atk_base)
    {
        int is_def_base_exit = 0;
        int is_atk_base_exit = 0;
        int i = 0, j = 0, def_num = 0, atk_num = 0;

        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                if (s[i][j] == def_base) {
                    is_def_base_exit = 1;
                }
                if (s[i][j] == atk_base) {
                    is_atk_base_exit = 1;
                }
                if (s[i][j]->side == def)
                    def_num++;
                else if (s[i][j]->side == atk)
                    atk_num++;
            }
        }
        cout << "********************" << endl;
        cout << "进攻方剩余" << atk_num << "士兵" << endl;
        cout << "防守方剩余" << def_num << "士兵" << endl;

        if (is_def_base_exit == 0 && is_atk_base_exit != 0 || def_num == 0 && atk_num == 0 && def_base->hp < atk_base->hp)
        {
            cout << "战斗结束，进攻方胜利！" << endl;
            cout << "********************" << endl;
            getchar();
            exit(0);
        }
        else if (is_def_base_exit != 0 && is_atk_base_exit == 0 || def_num == 0 && atk_num == 0 && def_base->hp > atk_base->hp)
        {
            cout << "战斗结束，防守方胜利！" << endl;
            cout << "********************" << endl;
            getchar();
            //getchar();
            exit(0);
        }
        else if (def_num == 0 && atk_num == 0 && def_base->hp == atk_base->hp) {
            cout << "战斗结束，双方平局！" << endl;
            cout << "********************" << endl;
            getchar();
            // getchar();
            exit(0);
        }
        cout << "********************" << endl;
    }

    int choice_war_mode()
    {
        char choice;
        cout << "请选择对战模式 1、100vs100   2、金钱模式  3、退出" << endl;
        choice = getchar();
        getchar();
        if (choice == '1')
            return 1;
        else if (choice == '2')
            return 2;
        else
            exit(0);
    }

    //百人模式
    void  hundred_mode(Soldier***&s,Soldier*& def_base, Soldier*& atk_base)
    {
        cout << "双方可以配置100人" << endl;
        cout << "现在是防守方配置兵力和基地阶段" << endl;

        int type, soldier_number, i = 0, j = 0, k = 0, sum = 0, max_number = 100;

       // init_generate_block(s, ROW_MAX, COL_MAX);
        i = 0, j = 0;
        //char pos[2] = { 0,0 };
        int pos[2] = { 0,0 };
        int is_def_base_init = 0;
        int is_atk_base_init = 0;
        while (1)
        {
            cout << "请选择要配置的兵种或基地： 1、弓箭手 2、步兵 3、骑兵 4、基地" << endl;
            cin >> type;
            switch (type)
            {
            case 1:
            {
                cout << "还可以配置" << max_number - sum << "个士兵" << endl;
                cout << "请输入人数：";
                cin >> def_base->total_bowman_num;
                if (def_base->total_bowman_num > max_number - sum)
                {
                    cout << "超出人数范围，为您配置" << max_number - sum << "个弓箭手" << endl;
                    def_base->total_bowman_num = max_number - sum;
                }
                sum = sum + def_base->total_bowman_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Bowman(bowman, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= COL_MAX)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }
                */
                break;
            }
            case 2:
            {
                cout << "还可以配置" << max_number - sum << "个士兵" << endl;
                cout << "请输入人数：";
                cin >> def_base->total_footman_num;
                if (def_base->total_footman_num > max_number - sum)
                {
                    cout << "超出人数范围，为您配置" << max_number - sum << "个步兵" << endl;
                    def_base->total_footman_num = max_number - sum;
                }
                sum = sum + def_base->total_footman_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Footman(footman, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= COL_MAX)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }
                */
                break;
            }
            case 3:
            {
                cout << "还可以配置" << max_number - sum << "个士兵" << endl;
                cout << "请输入人数：";
                cin >> def_base->total_knight_num;
                if (def_base->total_knight_num > max_number - sum)
                {
                    cout << "超出人数范围，为您配置" << max_number - sum << "个骑兵" << endl;
                    def_base->total_knight_num = max_number - sum;
                }
                sum = sum + def_base->total_knight_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Knight(knight, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= COL_MAX)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }*/
                break;
            }
            case 4:
            {
                cout << "请输入防守方基地的坐标:" << endl;
                cout << "请输入防守方基地的行数:（棋盘从上到下行数增大）" << endl;
                cin >> def_base->pos[0];
                cout << "请输入防守方基地的列数:（棋盘从左到右列数增大）" << endl;
                cin >> def_base->pos[1];
                cout << "防守方基地坐标已成功配置！" << endl;
                is_def_base_init = 1;
                s[def_base->pos[0]][def_base->pos[1]] = def_base;
                break;
            }
            default:
                break;

            }

            if (sum >= max_number && is_def_base_init == 1)
                break;

        }//end while


        cout << "现在是进攻方配置兵力或基地阶段" << endl;

        sum = 0, i = ROW_MAX - 1, j = COL_MAX - 1;
        pos[0] = i, pos[1] = j;
        while (1)
        {
            cout << "请选择要配置的兵种或基地： 1、弓箭手 2、步兵 3、骑兵 4、基地" << endl;
            cin >> type;
            switch (type)
            {
            case 1:
            {
                cout << "还可以配置" << max_number - sum << "个士兵" << endl;
                cout << "请输入人数：";
                cin >> atk_base->total_bowman_num;
                if (atk_base->total_bowman_num > max_number - sum)
                {
                    cout << "超出人数范围，为您配置" << max_number - sum << "个弓箭手" << endl;
                    atk_base->total_bowman_num = max_number - sum;
                }
                sum = sum +atk_base->total_bowman_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Bowman(bowman, atk, pos);
                    pos[1]--, j--;
                    if (pos[1] < 0)
                        pos[1] = COL_MAX - 1, pos[0]--, i--, j = COL_MAX - 1;

                }*/
                break;
            }
            case 2:
            {
                cout << "还可以配置" << max_number - sum << "个士兵" << endl;
                cout << "请输入人数：";
                cin >> atk_base->total_footman_num;
                if (atk_base->total_footman_num > max_number - sum)
                {
                    cout << "超出人数范围，为您配置" << max_number - sum << "个步兵" << endl;
                    atk_base->total_footman_num = max_number - sum;
                }
                sum = sum + atk_base->total_footman_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Footman(footman, atk, pos);
                    pos[1]--, j--;
                    if (pos[1] < 0)
                        pos[1] = COL_MAX - 1, pos[0]--, i--, j = COL_MAX - 1;

                }
                */
                break;
            }
            case 3:
            {
                cout << "还可以配置" << max_number - sum << "个士兵" << endl;
                cout << "请输入人数：";
                cin >> atk_base->total_knight_num;
                if (atk_base->total_knight_num > max_number - sum)
                {
                    cout << "超出人数范围，为您配置" << max_number - sum << "个骑兵" << endl;
                    atk_base->total_knight_num = max_number - sum;
                }
                sum = sum + atk_base->total_knight_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Knight(knight, atk, pos);
                    pos[1]--, j--;
                    if (pos[1] < 0)
                        pos[1] = COL_MAX - 1, pos[0]--, i--, j = COL_MAX - 1;

                }*/
                break;
            }
            case 4:
            {
                cout << "请输入进攻方基地的坐标:" << endl;
                cout << "请输入进攻方基地的行数:（棋盘从上到下行数增大）" << endl;
                cin >> atk_base->pos[0];
                cout << "请输入进攻方基地的列数:（棋盘从左到右列数增大）" << endl;
                cin >> atk_base->pos[1];
                cout << "进攻方基地坐标已成功配置！" << endl;
                is_atk_base_init = 1;
               s[atk_base->pos[0]][atk_base->pos[1]] = atk_base;
                break;
            }
            default:
                break;

            }
            if (sum >= max_number && is_atk_base_init == 1)
                break;
        }//end while

      // start_war(s, ROW_MAX, COL_MAX);
        return;
    }





    //金钱模式
    void money_mode(Soldier***&s,Soldier*&atk_base,Soldier*&def_base)
    {
        int  is_atk_base_init = 0;
        int  is_def_base_init = 0;
        cout << "请输入金钱数量" << endl;
        int money, type, soldier_number, i, j, k, row, col;
        cin >> money;
        int temp_money = money;
        row = ROW_MAX;
        col = COL_MAX;
        // col = money / CHEAPEST_SOLDIER;
         /*
         if (col > COL_MAX)
         {
             row = col / COL_MAX + 1;
             col = COL_MAX;
         }
         else
             row = 1;
         row = row * 2 + 10;*/
 
      //  init_generate_block(s, ROW_MAX, COL_MAX);
        cout << "现在是防守方配置兵力" << endl;
        //char pos[2] = { 0,0 };
        int pos[2] = { 0,0 };
        int sum = 0;
        i = 0, j = 0;
        while (1)
        {
            if (money < CHEAPEST_SOLDIER && is_def_base_init == 1)
                break;
            cout << "还有" << money << "金钱可以使用" << endl;
            cout << "请选择要配置的兵种或基地： 1、弓箭手 2、步兵 3、骑兵 4、基地" << endl;
            cin >> type;
            switch (type)
            {
            case 1:
            {
                cout << "还可以购买" << money / BOWMAN_PRICE << "个弓箭手" << endl;
                cout << "请输入人数：";
                cin >> def_base->total_bowman_num;
                if (def_base->total_bowman_num > money / BOWMAN_PRICE)
                {
                    def_base->total_bowman_num = money / BOWMAN_PRICE;
                    cout << "钱数不够，为您配置" << def_base->total_bowman_num << "个弓箭手" << endl;
                }
                money = money - def_base->total_bowman_num * BOWMAN_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {
                    s[i][j] = new Bowman(bowman, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }*/
                break;
            }
            case 2:
            {
                cout << "还可以购买" << money / FOOTMAN_PRICE << "个步兵" << endl;
                cout << "请输入人数：";
                cin >> def_base->total_footman_num;
                if (def_base->total_footman_num > money / FOOTMAN_PRICE)
                {
                    def_base->total_footman_num = money / FOOTMAN_PRICE;
                    cout << "钱数不够，为您配置" << def_base->total_footman_num << "个步兵" << endl;
                }
                money = money - def_base->total_footman_num * FOOTMAN_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Footman(footman, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }*/
                break;
            }
            case 3:
            {
                cout << "还可以购买" << money / KNIGHT_PRICE << "个骑兵" << endl;
                cout << "请输入人数：";
                cin >> def_base->total_knight_num;
                if (def_base->total_knight_num > money / KNIGHT_PRICE)
                {
                    def_base->total_knight_num = money / KNIGHT_PRICE;
                    cout << "钱数不够，为您配置" << def_base->total_knight_num << "个骑兵" << endl;
                }
                money = money - def_base->total_knight_num * KNIGHT_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Knight(knight, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }*/
                break;
            }
            case 4:
            {
                cout << "请输入防守方基地的坐标:" << endl;
                cout << "请输入防守方基地的行数:（棋盘从上到下行数增大）" << endl;
                cin >> def_base->pos[0];
                cout << "请输入防守方基地的列数:（棋盘从左到右列数增大）" << endl;
                cin >> def_base->pos[1];
                cout << "防守方基地坐标已成功配置！" << endl;
                is_def_base_init = 1;
                s[def_base->pos[0]][def_base->pos[1]] = def_base;
                break;
            }
            default:
                break;
            }
        }

        cout << "现在是进攻方配置兵力阶段" << endl;
        sum = 0, i = row - 1, j = 0;
        pos[0] = i, pos[1] = j;
        money = temp_money;
        while (1)
        {
            if (money < CHEAPEST_SOLDIER && is_atk_base_init == 1)
                break;
            cout << "还有" << money << "金钱可以使用" << endl;
            cout << "请选择要配置的兵种： 1、弓箭手 2、步兵 3、骑兵  4、基地" << endl;
            cin >> type;
            switch (type)
            {
            case 1:
            {
                cout << "还可以购买" << money / BOWMAN_PRICE << "个弓箭手" << endl;
                cout << "请输入人数：";
                cin >> atk_base->total_bowman_num;
                if (atk_base->total_bowman_num > money / BOWMAN_PRICE)
                {
                    atk_base->total_bowman_num = money / BOWMAN_PRICE;
                    cout << "钱数不够，为您配置" << atk_base->total_bowman_num << "个弓箭手" << endl;
                }
                money = money - atk_base->total_bowman_num * BOWMAN_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Bowman(bowman, atk, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]--, i--, j = 0;

                }*/
                break;
            }
            case 2:
            {
                cout << "还可以购买" << money / FOOTMAN_PRICE << "个步兵" << endl;
                cout << "请输入人数：";
                cin >> atk_base->total_footman_num;
                if (atk_base->total_footman_num / FOOTMAN_PRICE)
                {
                    atk_base->total_footman_num / FOOTMAN_PRICE;
                    cout << "钱数不够，为您配置" << atk_base->total_footman_num << "个步兵" << endl;
                }
                money = money - atk_base->total_footman_num * FOOTMAN_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Footman(footman, atk, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]--, i--, j = 0;

                }*/
                break;
            }
            case 3:
            {
                cout << "还可以购买" << money / KNIGHT_PRICE << "个骑兵" << endl;
                cout << "请输入人数：";
                cin >> atk_base->total_knight_num;
                if (atk_base->total_knight_num > money / KNIGHT_PRICE)
                {
                    atk_base->total_knight_num = money / KNIGHT_PRICE;
                    cout << "钱数不够，为您配置" << atk_base->total_knight_num << "个骑兵" << endl;
                }
                money = money - atk_base->total_knight_num * KNIGHT_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Knight(knight, atk, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]--, i--, j = 0;

                }*/
                break;
            }
            case 4:
            {
                cout << "请输入进攻方基地的坐标:" << endl;
                cout << "请输入进攻方基地的行数:（棋盘从上到下行数增大）" << endl;
                cin >> atk_base->pos[0];
                cout << "请输入进攻方基地的列数:（棋盘从左到右列数增大）" << endl;
                cin >> atk_base->pos[1];
                cout << "进攻方基地坐标已成功配置！" << endl;
                is_atk_base_init = 1;
               s[atk_base->pos[0]][atk_base->pos[1]] = atk_base;
                break;
            }
            default:
                break;

            }
        }//end while

       // start_war(s, ROW_MAX, COL_MAX);
        return;
    }
};