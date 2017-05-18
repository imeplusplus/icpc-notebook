struct Date{
    int d,m,y;
    static int month[], monthsum[];
    Date() : d(1), m(1), y(1) {}
    Date(int d, int m, int y) : d(d), m(m), y(y) {}
    Date(int days) : d(1), m(1), y(1) {
        advance(days);
    }
    int mdays() {
        if(m!=2)
            return month[m];
        return 28+bissexto();
    }
    int ydays() {
        return 365+bissexto();
    }
    int msum() {
        return monthsum[m]+(bissexto() and m>2);
    }
    bool bissexto() {
        return (y%4 == 0 and y%100) or (y%400 == 0);
    }
    int count() {
        int ans = d-1 + msum();

        ans += 365*(y-1);
        ans += (y-1)/4;
        ans -= (y-1)/100;
        ans += (y-1)/400;

        return ans;
    }
    void advance(int days) {
        days += count();
        d = m = 1;
        y = 1 + days/366;
        days -= count();
        while(days >= ydays())
            days -= ydays(), y++;
        while(days >= mdays())
            days -= mdays(), m++;
        d += days;
    }
};
int Date::month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int Date::monthsum[] = {0,0,31,59,90,120,151,181,212,243,273,304,334,365};
