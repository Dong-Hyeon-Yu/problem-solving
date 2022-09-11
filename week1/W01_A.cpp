#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#define vi vector<int> 

using namespace std;

void calcalate(vi* inhaKingdom, int inhaMin, vi* biryolKingdom, int biryolMin);
int getGCD(vi* soldiers, int min);
vi getDivisorArray(int min);
int getFinal(vi* kingdom, int gcd);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t, n, m;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;

        vector<int> inhaKingdom = vector<int>(n);
        vector<int> biryolKingdom = vector<int>(m);
    
        int t;
        int inhaMin = 100000001;
        for (int i = 0; i < n; i++) 
        {
            cin >> t;
            inhaKingdom[i] = t;
            inhaMin = min(inhaMin, t);
        }

        int biryolMin = 100000001;
        for (int i = 0; i < m; i++)
        {
            cin >> t;
            biryolKingdom[i] = t;
            biryolMin = min(biryolMin, t);
        }

        calcalate(&inhaKingdom, inhaMin, &biryolKingdom, biryolMin);

    }
    
}

void calcalate(vi* inhaKingdom, int inhaMin, vi* biryolKingdom, int biryolMin)
{
    int inhaGCD = getGCD(inhaKingdom, inhaMin);
    int biryolGCD = getGCD(biryolKingdom, biryolMin);

    // 상대왕국의 GCD가 자신의 용병을 쓰러뜨리지 않는 것을 선택해야 함.
    cout << getFinal(inhaKingdom, biryolGCD) << " " << getFinal(biryolKingdom, inhaGCD) << '\n';
}

int getGCD(vi* soldiers, int min) 
{
    vi divisorArray = getDivisorArray(min);
    bool find;

    for (int divisor : divisorArray)
    {
        find = true;
        for (int soldier : *soldiers)
        {
            if (soldier % divisor != 0)
            {
                find = false;
                break;
            }
        }

        if (find)
            return divisor;
    }

    return 1;
}

/*
  가장 작은 수의 모든 약수을 구하는 함수
  TimeComplexity : O(root N) => 유클리드 호제법을 이용하면 O(log N) 가능
  return : 약수를 내림차순으로 리턴.
*/
vi getDivisorArray(int min) 
{
    vi divisorArray = vector<int>();
    divisorArray.push_back(min);

    for (int i = sqrt(min); i > 1; i--)
    {
        if (min % i == 0)
        {
            divisorArray.push_back(min/i);
            divisorArray.push_back(i);
        }
        
    }

    sort(divisorArray.begin(), divisorArray.end(), [](int a, int b) -> int {
        return a > b;
        });

    return divisorArray;
}

// 상대왕국의 GCD로, 자신의 용병을 쓰러뜨리지 않는 지 확인.
int getFinal(vi* kingdom, int gcd)
{
    for (int soldier : *kingdom)
        if (soldier % gcd == 0) return -1;
    
    return gcd;
}

