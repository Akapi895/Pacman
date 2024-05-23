#include "PetObjectASTAR.h"


std::pair<int, int> FindAns(int grid[][35], pair<int, int> src, pair<int, int> des) {
    map1 m;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 35; ++j) {
            int a;
           a = grid[i][j];
            char c;
            if (a == 0 || a == 6 || a == 8) c = 0;
            else c = 1;
            m.t[i][j] = c;
        }
    }
    m.init_map();
    point s(src.first, src.second), e( des.first, des.second );
    aStar as;

    if( as.search( s, e, m ) ) {
        std::list<point> path;
        int c = as.path( path );

        int cnt = 2;
        for( std::list<point>::iterator i = path.begin(); i != path.end(); i++ ) {
//            std::cout<< "(" << ( *i ).x << ", " << ( *i ).y << ") ";
            if (cnt == 1) {
                pair<int, int> ans = make_pair(( *i ).x, ( *i ).y);
                return ans;
            }
            cnt--;

        }
    }
}

int findDirectionFrom(int grid[][35], std::pair<int, int> src, std::pair<int, int> des) {
    pair<int, int> ans = FindAns(grid, src, des);
    if (src.first + 1 == ans.first && src.second == ans.second) return GO_RIGHT;
    if (src.first - 1 == ans.first && src.second == ans.second) return GO_LEFT;
    if (src.first == ans.first && src.second - 1 == ans.second) return GO_UP;
    if (src.first == ans.first && src.second + 1 == ans.second) return GO_DOWN;
}
