#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct uint128 {
    unsigned long long a;
    unsigned long long b;
};
static uint128 stringToUint128(string input, int length);
static char recoverByte(vector<uint128> alphabets, uint128 byte);
static int getHammingDistance(uint128 a, uint128 b);

int main()
{

    int t, m ,n;
    
    cin >> t;
    while (t--)
    {
        cin >> m >> n;

        string byte;
        vector<uint128> alphabets;
        for (int i = 0; i < m; i++)  // 시간복잡도는 O(n) * m = O(nm)
        {
            cin >> byte;
            alphabets.push_back(stringToUint128(byte, n));
        }
        
        int l;
        uint128 current_byte_to_recover;
        string bits;
        cin >> l >> bits;
        for (size_t i = 0; i < l/n; i++)  // 시간복잡도는 O(nm) * l/n = O(ml)
        {
            current_byte_to_recover = stringToUint128(bits.substr(i*n, n), n);
            cout << recoverByte(alphabets, current_byte_to_recover);
        }
        cout << "\n";
    }
}

/**
 * 문자열로 주어진 비트 sequence 를 unsigned 128 bits 숫자형으로 변환하는 함수
 * stooull 의 시간복잡도는 문자열 길이에 비례함 -> O(n)
 * 문자열 길이 length를 n이라고 하면 총 시간복잡도는 O(n), (단 n은 [1, 128] 범위)
 */
uint128 stringToUint128(string input, int length)
{
    if (length <= 64)
        return uint128({ 0, stoull(input,0,2) });
    else
        return uint128({
                stoull(input.substr(0, length - 64),0,2),
                stoull(input.substr(length - 64),0,2)
            });
}

/**
 * 주어진 byte 에 가장 근사한 알파벳을 골라내는 함수.
 * byte 와 모든 알파벳의 거리를 계산한다.
 * 알파벳의 개수를 m개, byte 의 비트 길이를 n 이라고 하면, 시간복잡도는 O(mn) 이다. 
 * (단, m 은 [1, 26], n은 [1, 128] 범위이다.)
 **/
char recoverByte(vector<uint128> alphabets, uint128 byte)
{
    int min_dist = 99999, hamming_dist=99999, res = 0;
    for (int i = 0; i < alphabets.size(); i++)
    {
        hamming_dist = getHammingDistance(alphabets[i], byte);
        if (hamming_dist < min_dist)
        {
            min_dist = hamming_dist;
            res = i;
        }
    }
    return res + 65;
}


/**
 * 주어진 두 bits sequence 의 Hamming distance 를 구하는 함수.
 * (1) 두 수를 xor 하여 다른 bits 만 골라낸 다음,
 * (2) 비트를 순회하면서 1의 개수를 센다.
 * 
 * 두 수의 bits 길이를 n라고 하면 O(n) 의 시간 복잡도를 갖는다. (단, n 는 [1, 128] 범위)
 */
int getHammingDistance(uint128 a, uint128 b)
{
    int dist = 0;
    unsigned long long c[2] = {
        a.a ^ b.a, 
        a.b ^ b.b
    };
    
    for (unsigned long long _c : c)
    {
        do {
            if (_c & 1) dist += 1;
        } while (_c >>= 1);
    }

    return dist;
}

