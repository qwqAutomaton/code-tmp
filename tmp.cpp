#include <cstdio>
#include <vector>
using namespace std;
vector<int> l;
int Siz() {
    l.push_back(0);
    return l.size();
}
int main() {
    Siz();
    for (int i = 1; i < 10; i++) {
//        l[i - 1] = Siz();
        l.push_back(0);
        l[i - 1] = l.size();
        printf("%d ", l[i - 1]);
    }
}

