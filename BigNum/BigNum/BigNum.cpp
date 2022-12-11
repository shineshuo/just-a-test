#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include<stdlib.h>
using namespace std;
const int maxn = 10005;
class bigNum {
    friend istream& operator>>(istream& in, bigNum& n);
    friend ostream& operator<<(istream& out, const bigNum& n);//此处const很关键，决定了能否直接输出非左值
private:
    int a[maxn], len;
    char sign;
public:
    bigNum() :len(0) { memset(a, 0, sizeof(a)); };
    bigNum(string s) { change(s); };
    bigNum(int n) { change(to_string(n)); };
    void change(string s)
    {
        if (s[0] == '-') {
            sign = '-';
            s.erase(s.begin());
        }
        else sign = '+';
        len = s.size();
        for (int i = len - 1; i >= 0; --i) a[len - 1 - i] = s[i] - '0';
    }
    void print()const
    {
        if (sign == '-') cout << this->sign;
        for (int i = len - 1; i >= 0; --i) cout << this->a[i];
    }

    bigNum add(const bigNum& rhs)const
    {
        bigNum ans;
        memset(ans.a, 0, sizeof(ans.a));
        int mlen = max(this->len, rhs.len), flag = 0;
        for (int i = 0; i < mlen; ++i) {
            ans.a[i] = this->a[i] + rhs.a[i] + flag;
            flag = 0;
            flag = ans.a[i] / 10;
            ans.a[i] %= 10;
        }
        if (flag) ans.a[mlen++] = 1;
        ans.len = mlen;
        return ans;
    }
    bigNum sub(const bigNum& rhs)const
    {
        bigNum ans;
        memset(ans.a, 0, sizeof(ans.a));
        int mlen = this->len;
        for (int i = 0; i < mlen; ++i) {
            ans.a[i] += this->a[i] - rhs.a[i];  //ans.a[i]=ans.a[i]+this->a[i]-rhs.a[i]
            if (ans.a[i] < 0) {
                ans.a[i] += 10;
                ans.a[i + 1] -= 1;
            }
        }
        while (!ans.a[mlen] && mlen > 0) --mlen;
        ans.len = mlen + 1;
        return ans;
    }
    bigNum mul(const bigNum& rhs)const
    {
        bigNum ans;
        memset(ans.a, 0, sizeof(ans.a));
        int mlen = this->len + rhs.len;
        for (int i = 0; i < this->len; ++i) {
            for (int j = 0; j < rhs.len; ++j) {
                ans.a[j + i] += this->a[i] * rhs.a[j];
                ans.a[j + i + 1] += ans.a[j + i] / 10;
                ans.a[j + i] %= 10;
            }
        }
        while (!ans.a[mlen] && mlen > 0) --mlen;
        ans.len = mlen + 1;
        return ans;
    }
public:
    bigNum operator+(const bigNum& rhs)const
    {
        return this->add(rhs);
    }
    bigNum operator-(const bigNum& rhs)const
    {
        if (*this < rhs) {
            bigNum ans = rhs.sub(*this);
            ans.sign = '-';
            return ans;
        }
        else return this->sub(rhs);
    }
    bigNum operator*(const bigNum& rhs)const
    {
        return this->mul(rhs);
    }
    bigNum operator*(const int& rhs)const
    {
        return this->mul(to_string(rhs));
    }
    bigNum& operator+=(const bigNum& rhs)
    {
        *this = *this + rhs;
        return *this;
    }
    bigNum& operator-=(const bigNum& rhs)
    {
        *this = *this - rhs;
        return *this;
    }
    bigNum operator/(const int& rhs)const
    {
        bigNum ans;
        string s;
        int num = 0;
        for (int i = len - 1; i >= 0; --i) {
            s.push_back((num * 10 + a[i]) / rhs + 48);
            num = (num * 10 + a[i]) % rhs;
        }
        for (int i = 0; s[0] == 48; ++i) s.erase(s.begin());
        if (s.empty()) ans = 0;
        else ans = s;
        return ans;
    }
    bigNum operator%(const int& rhs)const
    {
        bigNum ans;
        string s;
        int num = 0;
        for (int i = len - 1; i >= 0; --i) {
            s.push_back((num * 10 + a[i]) / rhs + 48);
            num = (num * 10 + a[i]) % rhs;
        }
        return num;
    }
    bool operator<(const bigNum& rhs)const
    {
        if (this->len < rhs.len) return 1;
        else if (this->len > rhs.len) return 0;
        else {
            int flag = 0;
            for (int i = this->len - 1; i >= 0; --i) {
                if (this->a[i] > rhs.a[i]) {
                    flag = 0;
                    break;
                }
                if (this->a[i] < rhs.a[i]) {
                    flag = 1;
                    break;
                }
            }
            return flag;
        }
    }
    bool operator>(const bigNum& rhs)const
    {
        if (this->len > rhs.len) return 1;
        else if (this->len < rhs.len) return 0;
        else {
            int flag = 0;
            for (int i = this->len - 1; i >= 0; --i) {
                if (this->a[i] < rhs.a[i]) {
                    flag = 0;
                    break;
                }
                if (this->a[i] > rhs.a[i]) {
                    flag = 1;
                    break;
                }
            }
            return flag;
        }
    }
    bool operator==(const bigNum& rhs) const
    {
        int flag = 0;
        if (this->len == rhs.len) {
            flag = 1;
            for (int i = 0; i < this->len; ++i) {
                if (this->a[i] != rhs.a[i]) {
                    flag = 0;
                    break;
                }
            }
        }
        return flag;
    }
};
istream& operator>>(istream& in, bigNum& n)
{
    string s;
    in >> s;
    n.change(s);
    return in;
}
ostream& operator<<(ostream& out, const bigNum& n)
{
    n.print();
    return out;
}
int main()
{
    int b;
    bigNum a, c;
    cin >> a >> c >> b;
    cout << a % b << endl;
    cout << a * c << endl;
    cout << a + c << endl;
    cout << a - c << endl;
    cout << a / b << endl;
    system("pause");
    return 0;
}