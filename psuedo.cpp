#include <bits/stdc++.h>
#include "DCEL.h"


int main(){

    freopen()
    
    dcel = DCEL();

    vector<chain> L; //worry about initialization later

    //i want to know number of vertices in polygon
    int n = dcel.size();
    int m = 1;
    L[0] = {dcel.front()};

    while(n>3){
        vertex v1 = L[m-1].back();
        vertex v2 = v1.next;

        L[m] = {v1,v2};
        
        vector<vertex> cur = {v1,v2,v2.next};

        //ang will return true if angle<=180 
        while(ang(cur[0],cur[1],cur[2]) && ang(cur[1],cur[2],v1) && ang(cur[2],v1,v2) && (int)L.size()<n){
            L[m].add(cur[2]);
            cur[0] = cur[1];
            cur[1] = cur[2];
            cur[2] = cur[1].next;
        }

        if((int)L.size() != (int)dcel.size()){
            vector<vertex> LPVS = dcel.getLPVS(); //list of all notches
            while(LPVS>0){
                //we can make L[m] a class,in which we have the info of smallest rectangle bounding it 
                vector<pair<int,int>> box = L[m].boundingBox();
                bool Backward = false;
                auto check = [&](vectex v){
                    //check if in box
                };
                while(!Backward and LPVS.size()){
                    while(LPVS.size()){
                        vertex v = LPVS.back();
                        if(check(v)) break;
                        LPVS.pop_back();
                    }
                    if(LPVS.size()){
                        vertex v = LPVS.back();
                        if(L[m].find(v)){
                            while(!L[m].checkSide(v,L[m].back())){//checkside will use cross product
                                L[m].pop_back();
                            }  
                            Backward = true;
                        }
                        LPVS.pop_back();
                    }
                }

            }
        }

        if(L[m].back()!=v2){
            //we can either add v1 - L[m].back() edge to dcel now
            //or store L[m] in list of polygons
            //or remove L[m] from dcel completly, like in algo P = (P\Lm)U{first[Lm],last[Lm]}
            n = n - L[m].size()+2;
        }
        m++;
    } 

    return 0;
}