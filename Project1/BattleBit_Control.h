#pragma once
#include"define.h"
#include"BattleBit_View.h"
#include"BattleBit_Model.h"
#include<iostream>
#include<thread>
#include<mutex>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include<omp.h>
#include<future>
using namespace std;
using namespace sf;
struct thread_data {
    int row;
    int col;
    int thread_num;
    int num;
};
class BattleBit_Control {
public:
    //Soldier& s= Soldier::getinstance();
    BattleBit_View** observers;//观察者数组
    int observer_num;//观察者的个数
    int atk_base_hp, def_base_hp;


BattleBit_View* battlebit_view;
Soldier *empty1;
Soldier *block;
Soldier* atk_base;
Soldier* def_base;
//Soldier* atk_super_soldier;
//Soldier* def_super_soldier;
Soldier*** s;

Texture mapTex;
Sprite map;
Texture blockTex[NUM_BLOCK];
Sprite block_mount[NUM_BLOCK];

BattleBit_Control() {
    int pos_base_init[2];
    empty1 = new Soldier();
    block = new Soldier();
    atk_base = new Base(base, atk, pos_base_init);
    def_base = new Base(base, def, pos_base_init);
    battlebit_view = new BattleBit_View();
    s = new Soldier * *[ROW_MAX];

    for (int i = 0; i < ROW_MAX; ++i)
        s[i] = new Soldier * [COL_MAX];


    for (int i = 0; i < ROW_MAX; ++i)
        for (int j = 0; j < COL_MAX; ++j)
        {
            s[i][j] = empty1;
        }
    atk_base_hp = 200, def_base_hp = 200;
    observers = new BattleBit_View * [100];//观察者数组
    observer_num = 0;//观察者的个数
}
void generate_super_soldier(Soldier***& s,int row, int col, Soldier*& atk_base, Soldier*& def_base) {
    int atk_supersoldier_row;
    int random_row_super = rand() % 2;
    if (random_row_super == 0) {
        if ((atk_supersoldier_row = atk_base->pos[0] + rand() % 3 + 1) >= ROW_MAX) {
            atk_supersoldier_row = ROW_MAX - 1;
        }
    }
    else {
        if ((atk_supersoldier_row = atk_base->pos[0] - rand() % 3 - 1) < 0) {
            atk_supersoldier_row = 0;
        }
    }

    int def_supersoldier_row;
    random_row_super = rand() % 2;
    if (random_row_super == 0) {
        if ((def_supersoldier_row = def_base->pos[0] + rand() % 3 + 1) >= ROW_MAX) {
            def_supersoldier_row = ROW_MAX - 1;
        }
    }
    else {
        if ((def_supersoldier_row = def_base->pos[0] - rand() % 3 - 1) < 0) {
            def_supersoldier_row = 0;
        }
    }

    int atk_supersoldier_col;
    int random_col_super = rand() % 2;
    if (random_col_super == 0) {
        if ((atk_supersoldier_col = atk_base->pos[0] + rand() % 3 + 1) >= COL_MAX) {
            atk_supersoldier_col = COL_MAX - 1;
        }
    }
    else {
        if ((atk_supersoldier_col = atk_base->pos[0] - rand() % 3 - 1) < 0) {
            atk_supersoldier_col = 0;
        }
    }

    int def_supersoldier_col;
    random_col_super = rand() % 2;
    if (random_col_super == 0) {
        if ((def_supersoldier_col = def_base->pos[0] + rand() % 3 + 1) >= COL_MAX) {
            def_supersoldier_col = COL_MAX - 1;
        }
    }
    else {
        if ((def_supersoldier_col = def_base->pos[0] - rand() % 3 - 1) < 0) {
            def_supersoldier_col = 0;
        }
    }

    int super_pos[2] = { def_supersoldier_row ,def_supersoldier_col };
    s[def_supersoldier_row][def_supersoldier_col] = new Super_soldier(super, def, super_pos);
   // s[def_supersoldier_row][def_supersoldier_col]->is_moved = 0;

    int super_pos1[2] = { atk_supersoldier_row ,atk_supersoldier_col };
    s[atk_supersoldier_row][atk_supersoldier_col] = new Super_soldier(super, atk, super_pos1);
   // s[atk_supersoldier_row][atk_supersoldier_col]->is_moved = 1;

}
void start_war(int row, int col)
{
    while (1)
    {
        int watch_mode = battlebit_view->select_mode();
        switch (watch_mode)
        {
        case 0:
        {
            
        //    char next;
        //    next = battlebit_view->hand_mode();
        //    while (next=='\n')
        //    {
           
                   // if (is_over(row, col))
                    //{
         //               battlebit_view->print_war_field(s, block, row, col);
           //             battlebit_view->print_war_state(s, row, col, def_base, atk_base);
                  //  }
          //          atk_base->generate_soldier(s, row, col, empty1);
           //         def_base->generate_soldier(s, row, col, empty1);
            //        fight(row, col);

             //       next = battlebit_view->hand_mode();
                /*
                battlebit_view->print_war_field(s, block, row, col);
                battlebit_view->print_war_state(s, row, col, def_base, atk_base);
                atk_base->generate_soldier(s, row, col, empty1);
                def_base->generate_soldier(s, row, col, empty1);
                fight(row, col);

                next = battlebit_view->hand_mode();*/
         
            goto L1;
            break;
            /*
            while (1)
            {
                if (is_over(row, col))
                {
                    battlebit_view->print_war_field(s, block, row, col);
                    battlebit_view->print_war_state(s, row, col, def_base, atk_base);
                }
                atk_base->generate_soldier(s, row, col, empty1);
                def_base->generate_soldier(s, row, col, empty1);
                fight(row, col);

            }
            break;
            */
        }
        case 1:
        {
            char next;
            next = battlebit_view->hand_mode();
            
            init_generate_block(row, col);
            while (next=='\n')
            {
               
           
                sf::RenderWindow window(VideoMode(1000, 1000), "BattleBit");

                if (!mapTex.loadFromFile("Textures/map.png"))
                    throw "Could not load map.png!";
                window.setFramerateLimit(60);
                map.setTexture(mapTex);
                map.setScale(Vector2f(1.11111111f, 1.11111111f));
              
              
                while (window.isOpen()) {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                            window.close();
                    }


                    atk_base->generate_soldier(s, row, col, empty1);
                    def_base->generate_soldier(s, row, col, empty1);
                    battlebit_view->print_war_field(s, block, row, col);
                    battlebit_view->print_war_state(s, row, col, def_base, atk_base);

                    //Draw
                    window.clear();

                    window.draw(map);


                    for (int i = 0; i < NUM_BLOCK; i++) {
                        window.draw(block_mount[i]);
                    }


                    for (int i = 0; i < row; i++) {
                        for (int j = 0; j < col; j++) {

                            if (s[i][j]->type == base) {
                                if (s[i][j]->side == atk) {
                                    s[i][j]->soldierTex.loadFromFile("Textures/atk_base.png");
                                    s[i][j]->soldierSprite.setTexture(s[i][j]->soldierTex);
                                    s[i][j]->soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
                                    s[i][j]->soldierSprite.setPosition(Vector2f(33.33333333 * s[i][j]->pos[1], 33.33333333 * s[i][j]->pos[0]));
                                }
                                else  if (s[i][j]->side == def) {
                                    s[i][j]->soldierTex.loadFromFile("Textures/def_base.png");
                                    s[i][j]->soldierSprite.setTexture(s[i][j]->soldierTex);
                                    s[i][j]->soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
                                    s[i][j]->soldierSprite.setPosition(Vector2f(33.33333333 * s[i][j]->pos[1], 33.33333333 * s[i][j]->pos[0]));
                                }
                            }
                            window.draw(s[i][j]->soldierSprite);
                        }
                    }
                    // window.draw(atk_base->soldierSprite);
                   //  window.draw(def_base->soldierSprite);

                    window.display();
                    //while (next == '\n')
                    //{

                    fight(row, col);
                
                next = battlebit_view->hand_mode();
       


                        
                        //  }

                    
                }


            }
            break;

        }
        case 2:

        {
            generate_super_soldier(s, row, col, atk_base, def_base);
            init_generate_block(row, col);
            char next;
            char nexts[3]={'Q','Q'};
            sf::RenderWindow window(VideoMode(1000, 1000), "BattleBit");
           
            if (!mapTex.loadFromFile("Textures/map.png"))
                throw "Could not load map.png!";
            window.setFramerateLimit(60);
            map.setTexture(mapTex);
            map.setScale(Vector2f(1.11111111f,1.11111111f));

            next = battlebit_view->hand_mode();

            

            int who_move=0;

            while (next=='\n') {
                while (window.isOpen()) {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                            window.close();
                    }
                
                 
                    atk_base->generate_soldier(s, row, col, empty1);
                    def_base->generate_soldier(s, row, col, empty1);
                    battlebit_view->print_war_field(s, block, row, col);
                    battlebit_view->print_war_state(s, row, col, def_base, atk_base);

                    for (int i = 0; i < row; i++) {
                        for (int j = 0; j < col; j++) {

                            if (s[i][j]->type == super) {
                                if (s[i][j]->side == atk) {
                                    s[i][j]->move_tag = nexts[0];
                                    s[i][j]->move(s, row, col, empty1, atk_base, def_base);
                                }
                                else  if (s[i][j]->side == def) {
                                    s[i][j]->move_tag = nexts[1];
                                    s[i][j]->move(s, row, col, empty1, atk_base, def_base);
                                }
                            }

                        }
                    }
                    //Draw
                    window.clear();

                    window.draw(map);
                  
                    for (int i = 0; i < NUM_BLOCK; i++) {
                        window.draw(block_mount[i]);
                    }
                   
                    for (int i = 0; i < row; i++) {
                        for (int j = 0; j < col; j++) {
                            
                           if (s[i][j]->type == base) {
                               if (s[i][j]->side == atk) {
                                   s[i][j]->soldierTex.loadFromFile("Textures/atk_base.png");
                                   s[i][j]->soldierSprite.setTexture(s[i][j]->soldierTex);
                                   s[i][j]->soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
                                   s[i][j]->soldierSprite.setPosition(Vector2f(33.33333333 * s[i][j]->pos[1], 33.33333333 * s[i][j]->pos[0]));
                               }
                               else  if (s[i][j]->side == def) {
                                   s[i][j]->soldierTex.loadFromFile("Textures/def_base.png");
                                   s[i][j]->soldierSprite.setTexture(s[i][j]->soldierTex);
                                   s[i][j]->soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
                                   s[i][j]->soldierSprite.setPosition(Vector2f(33.33333333 * s[i][j]->pos[1], 33.33333333 * s[i][j]->pos[0]));
                               }
                            }
                           window.draw(s[i][j]->soldierSprite);
                        }
                    }
                   // window.draw(atk_base->soldierSprite);
                  //  window.draw(def_base->soldierSprite);

                    window.display();

                    /*int i, j;

                    for (i = 0; i < row; i++) {
                           for( j=0;j<col&&(s[i][j]->type!=super|| s[i][j]->side!=atk); j++) {}
                        }
                    cout << i << j << endl;
                            s[i][j]->move_tag = nexts[0];
                            s[i][j]->move(s, row, col, empty1, atk_base, def_base);

                   for (i = 0; i < row; i++) {
                                for (j = 0; j < col && (s[i][j]->type != super || s[i][j]->side != def); j++) {}
                            }
                            s[i][j]->move_tag = nexts[1];
                            s[i][j]->move(s, row, col, empty1, atk_base, def_base);
                            */
               

                            fight(row, col);
                    //while (next == '\n')
                    //{
                   

                   // if ((Keyboard::isKeyPressed(Keyboard::W)  || Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D)) && (who_move == 0 || who_move == 1)) {
                     //   if (who_move == 0) {
                        //    int i, j;
                        //    for (i = 0; i < row; i++) {
                        //        for( j=0;j<col&&(s[i][j]->type!=super|| s[i][j]->side!=atk); j++) {}
                      //      }
                       //     s[i][j]->move(s, row, col, empty1, atk_base, def_base);

                     //   }
                     //   else
                     //   if (who_move == 1) {
                     //       int i, j;
                     //       for (i = 0; i < row; i++) {
                      //          for (j = 0; j < col && (s[i][j]->type != super || s[i][j]->side != def); j++) {}
                     //       }
                     //       s[i][j]->move(s, row, col, empty1, atk_base, def_base);

                  //      }
                  //  }
                  //  else if (next == '\n' && who_move == 2) {
                       // fight(row, col);
                  //  }

                  //  if (who_move < 2) {
                   //     who_move++;
                   // }
                  //  else {
                  //      who_move = 0;
                  //  }

                        for (int i = 0; i < 2; i++)
                        {
                            nexts[i] = battlebit_view->hand_mode();
                        }
                        next= battlebit_view->hand_mode();

                 


                    //  }

                }
            }

            break;
        }
        default:
            break;
        }

    }      
    L1:
    return;
}

        void notifyObservers(Soldier * atk_base, Soldier * def_base) {
            if (atk_base_hp != 0 && atk_base_hp > atk_base->hp)
            {
                atk_base_hp = atk_base->hp;
                for (int i = 0; i < observer_num; i++) {
                    observers[i]->update(atk_base_hp, 1);
                }

            }

            if (def_base_hp != 0 && def_base_hp > def_base->hp)
            {
                def_base_hp = def_base->hp;
                for (int i = 0; i < observer_num; i++) {
                    observers[i]->update(def_base_hp, 2);
                }

            }
        }


        void registerObserver(BattleBit_View * o) {
            observers[observer_num] = o;
            observer_num++;
        }


        void removeObserver(BattleBit_View * o) {
            int i;
            for (i = 0; i < observer_num && o->name != observers[i]->name; i++);
            if (i == observer_num)
            {
                cout << "error to remove" << endl;
            }
            else
            {
                for (int j = i; j < observer_num; j++) {
                    observers[j] = observers[j + 1];
                }
                observer_num--;
            }
        }
     //   s = Soldier::getinstance();
      //  battlebit_view = new BattleBit_View();
    

    void  init_generate_block( int row, int col) {
        int row1, col1;
        srand(time(NULL));
  
        /*
        for (int row2 = 0; row2 < ROW_MAX; row2++) {
            for (int col2 = 0; col2 < COL_MAX; col2++) {
                s[row2][col2] = empty1;
            }
        }*/
        for (int count = NUM_BLOCK; count > 0; ) {
            row1 = rand() % ROW_MAX;
            col1 = rand() % COL_MAX;
            if (row1 != 0 && row1 != ROW_MAX-1 && col1 != 0 && col1 != COL_MAX-1&&s[row1][col1]==empty1) {
                if (s[row1 + 1][col1 + 1] != block && s[row1 - 1][col1 - 1] != block && s[row1 + 1][col1 - 1] != block && s[row1 - 1][col1 + 1] != block) {
                    //if确保不会有士兵被卡住或者基地被障碍物围住
                    s[row1][col1] = block;
                    int decide_block = rand() % 3;

                    if (decide_block == 0) {
                        blockTex[count - 1].loadFromFile("Textures/mountain.png");
                    }
                    else if (decide_block == 1) {
                        blockTex[count - 1].loadFromFile("Textures/tree.png");
                    }
                    else if (decide_block == 2) {
                        blockTex[count - 1].loadFromFile("Textures/river.png");
                    }

                    block_mount[count - 1].setTexture(blockTex[count - 1]);
                    block_mount[count - 1].setScale(Vector2f(0.22222222f, 0.22222222f));
                    block_mount[count - 1].setPosition(Vector2f(33.33333333 * col1, 33.33333333 * row1));
                    count--;
                }
            }
        }
    }
    //mutex lock1;
   // mutex lock2;
   void fight_thread(int row, int col, int row_min, int row_max, int col_min, int col_max,int sleep) {
      // srand(row_min);
     //  if (sleep % 2 == 1) {
          // this_thread::sleep_for(chrono::microseconds(1000));
      // }
       cout << row_min << endl;
      //cout << "线程";
       /* cout << "线程" << num;
      
        int row_min, row_max, col_min, col_max;
        int row_count = row / thread_num;
        int col_count = col / thread_num;
        row_min = (num - 1) * row_count;
        row_max = num * row_count - 1;
        col_min = (num - 1) * col_count;
        col_max = num * col_count - 1;
        cout << row_min << endl;
        cout << col_min << endl;*/
       // if (row_min == 0) {
          //  lock1.lock();
            int i = 0, j = 0;
//#pragma omp parallel for shared(s)
            for (i = row_min; i < row_max; ++i)
            {
                for (j = col_min; j < col_max; ++j)
                {
                   
                    if (s[i][j]->side == atk && s[i][j] != atk_base)
                    {
                        s[i][j]->move(s, row, col, empty1, atk_base, def_base);
                    }

                }
            }
//#pragma omp parallel for
//#pragma omp parallel for shared(sum)
            for (i = row_min; i < row_max; ++i)
            {
                for (j = col_min; j < col_max; ++j)
                {
                    if (s[i][j]->side == def && s[i][j] != def_base)
                    {
                        s[i][j]->move(s, row, col, empty1, atk_base, def_base);
                    }

                }
            }
          //  lock1.unlock();
       // }
     /*   else if (row_min == 10) {
            lock1.lock();
            lock2.lock();
            lock2.unlock();
            lock1.unlock();
        }
        else if (row_min == 20) {
            lock2.lock();
            lock2.unlock();
        }
        */
    }

    void fight( int row, int col)
    {
        int i = 0, j = 0;
      #pragma omp parallel for//并行初始化
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                s[i][j]->is_moved = 0;
            }
        }
        //9个线程并发操作
      // int count = 0;
      // srand(time(NULL));
      //  future<void> t[9];
       // for (int i = 0; i < 30; i = i + 10) {
        //    for (int j = 0; j < 30; j = j + 10) {
         //       t[count] = async(&BattleBit_Control::fight_thread, this, ref(row), ref(col), i, i+10 , j, j+10 ,rand()%1000);
         //       t[count].get();
         //   }
       // }
        /*
        
            //thread t1(&BattleBit_Control::fight_thread, this,ref(row), ref(col), 0, 9,0,29);
          //  t1.join();
           // thread t2(&BattleBit_Control::fight_thread, this,ref(row), ref(col), 10, 19,0,29);
          //  t2.join();
           // thread t3(&BattleBit_Control::fight_thread, this,ref(row), ref(col), 20,29,0,29);
           // t3.join();
           /* thread t4(&BattleBit_Control::fight_thread, this,ref(row), ref(col), 10, 19, 0, 9);
            t4.join();
            thread t5(&BattleBit_Control::fight_thread, this,ref(row), ref(col), 10, 19, 10, 19);
            t5.join();
            thread t6(&BattleBit_Control::fight_thread, this, ref(row), ref(col), 10, 19,20, 29);
            t6.join();
            thread t7(&BattleBit_Control::fight_thread, this, ref(row), ref(col), 20, 29, 0, 9);
            t7.join();
            thread t8(&BattleBit_Control::fight_thread, this, ref(row), ref(col), 20, 29, 10, 19);
            t8.join();
            thread t9(&BattleBit_Control::fight_thread, this, ref(row), ref(col), 20, 29,20, 29);
            t9.join();
           // thread t10(&BattleBit_Control::fight_thread, this, ref(row), ref(col), 10, 10);
           // t10.join();
           */

       for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                if (s[i][j]->side == atk && s[i][j] != atk_base && s[i][j]->type != super)
                {
                    s[i][j]->move(s,row, col,empty1, atk_base, def_base);
                }
                    
            }
        }
//
        for (i = row - 1; i >= 0; i--)
        {
            for (j = 0; j < col; j++)
            {
                if (s[i][j]->side == def&&s[i][j]!=def_base&&s[i][j]->type!=super)
                {
                    s[i][j]->move(s,row, col,empty1, atk_base, def_base);
                }
  
            }
        }
        notifyObservers(atk_base, def_base);
    }

    //判断战斗是否结束
    int is_over( int row, int col)
    {
        int is_def_base_exit = 0;
        int is_atk_base_exit = 0;
        int i = 0, j = 0, def_num = 0, atk_num = 0;
        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                if (s[i][j] ==def_base) {
                    is_def_base_exit = 1;
                }
                if (s[i][j] ==atk_base) {
                    is_atk_base_exit = 1;
                }
                if (s[i][j]->side == def)
                    def_num++;
                else if (s[i][j]->side == atk)
                    atk_num++;
            }
        }
        if (def_num == 0 && atk_num == 0 || is_atk_base_exit == 0 || is_def_base_exit == 0)
            return 1;
        else
            return 0;
    }



    void game_start(int row ,int col) {
        BattleBit_View *o = battlebit_view;
        registerObserver(o);
        battlebit_view->print_init_list();
        int sign = battlebit_view->choice_war_mode();
        if (sign == 1) {
            //init_generate_block(row, col);
            battlebit_view->hundred_mode(s,def_base,atk_base);
            start_war(row, col);
        }
        else if (sign == 2) {
            //init_generate_block(row, col);
            battlebit_view->money_mode(s, atk_base, def_base);
            start_war(row, col);
        }
        else if (sign == 3) {
            exit(0);
        }
        else {
            cout << "error" << endl;
            exit(0);
        }
    }
};
