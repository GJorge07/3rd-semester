#include <stdio.h>

int main() {

    int T;
    scanf("%d", &T);

    while(T--) {

        long long L;
        int N;

        scanf("%lld %d", &L, &N);

        long long min_time = 0;
        long long max_time = 0;

        for(int i = 0; i < N; i++) {

            long long p;
            scanf("%lld", &p);

            long long a = p;
            long long b = L - p;

            if(a < b) {
                if(a > min_time) min_time = a;
                if(b > max_time) max_time = b;
            } else {
                if(b > min_time) min_time = b;
                if(a > max_time) max_time = a;
            }
        }

        printf("%lld %lld\n", min_time, max_time);
    }

    return 0;
}