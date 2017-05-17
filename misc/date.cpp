struct Date{
    int d,m,y;
    Date() : d(1), m(1), y(1) {}
    Date(int d, int m, int y) : d(d), m(m), y(y) {}
    int mdays() {
        switch(m) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return 31;
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                return 28+bissexto();
        }
    }
    int ydays() {
        return 365+bissexto();
    }
    bool bissexto() {
        return (y%4 == 0 and y%100) or (y%400 == 0);
    }
    int count() {
        int ans = d-1;

        int aux = m;
        while(--m >= 1)
            ans += mdays();
        m = aux;

        ans += 365*(y-1);
        ans += (y-1)/4;
        ans -= (y-1)/100;
        ans += (y-1)/400;

        return ans;
    }
    void advance(int days) {
        days += count();
        d = m = y = 1;
        int l = 1, r = 10000;
        while(l != r) {
            y = (l+r+1)/2;
            if(count() > days)
                r = y-1;
            else
                l = y;
        }
        y = l;
        days -= count();
        while(days >= mdays())
            days -= mdays(), m++;
        d += days;
    }
};
