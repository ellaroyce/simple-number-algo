//
//  main.cpp
//  lablab
//
//  Created by LA on 30/11/15.
//  Copyright © 2015 ellatyuryumina. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
unsigned int start_time, end_time;

long long randomPrimeNumber(const vector < long long > &primeNumbers, long long A, long long B) {
    for(long long  i = 0; i < primeNumbers.size(); i++) {
        if (primeNumbers[i] > A && primeNumbers[i] < B) {
            return primeNumbers[i];
        }
    }
    exit(0);
}

vector < long long > tableOfPrimeNumbers(long long  number){
    vector < long long > primeNumbers = {2,3,5,7,11,13,17};
    long long  h = 5, s = 25, p_n = 17;
    while(true){
        p_n = p_n + 2;
        long long k1 = 1;
        if (p_n > number)
            break;
        if (p_n > s){
            s = s + h;
            h = h + 1;
            s = s + h;
        }
        long long go_to_3 = 0;
        while (k1 < primeNumbers.size() && primeNumbers[k1] <= s){
            if (p_n % primeNumbers[k1] == 0) {
                go_to_3 = 1;
                break;
            }
            else {
                ++k1;
            }
        }
        if (go_to_3) {
            continue;
        } else {
            primeNumbers.push_back(p_n);
        }
    }
    return primeNumbers;
}

pair < long long , long long > input(){
    long long A, B;
    cout << endl << "Please, input a number A: ";
    cin >> A;
    cout << endl << "Please, input a number B: ";
    cin >> B;
    return {A,B};
}

bool checkInput(long long chislo1, long long chislo2){
    if (chislo1 + 1 < chislo2){
        return true;
    }
    else
    {
        cout << "[X] Error. Wrong Input! Try one more time";
        return false;
    }
}

bool checkB(long long chislo){
    if (chislo < 65536){
        return 1;
    }
    else
        return 0;
}

long long  gcd(long long chislo1, long long chislo2) {
    return chislo2 ? gcd (chislo2, chislo1 % chislo2) : chislo1;
}

long long  myPow(long long  chislo1, long long  chislo2){
    long long  result = 1;
    for (long long  i = 1; i < chislo2+1; i++){
        result = chislo1 * result;
    }
    
    return result;
}

long long  myPowMod(long long  chislo1, long long  chislo2, long long  mod){
    long long  result = 1;
    for (long long  i = 1; i < chislo2+1; i++){
        result = chislo1 * result;
        result = result % mod;
    }
    
    return result;
}

bool MillerRabin(long long  m){
    long long it, k, n, q, b, vichet;
    n = 0;
    if (gcd(6,m) == 1){
        long long  stepOne;
        stepOne = m - 1;
        while(stepOne%2 == 0){
            stepOne = stepOne / 2;
            ++n;
        }
        q = stepOne;
    }
    else
        return false;
    k = 20;
L3:
    k = k - 1;
    if (k == 0)
        return true;
    
    vichet = 1 + rand() % (m-1);
    
    b = myPowMod(vichet, q, m);
    if ((b%m == 1) || (b%m == m-1))
        goto L3;
    else
        it = 0;
    
    while (it < n){
        b = myPowMod(b,2,m);
        if (b == m-1)
            goto L3;
        else
            it++;
    }
    return false;
}

bool trustMe (long long A) {
    if (A%2 == 0) {
        return false;
    }
    for (long long i = 3; i * i <= A; i += 2) {
        if (A % i == 0) {
            return false;
        }
    }
    return true;
}

long long  findNumbers(const vector < long long > &primeNumbers, long long  A, long long  B){
    long long  q_A,q_B,k,k_1,k_2,k_n,k_s,counter = 0;
    long long  p,q;
    double alpha;
    cout << A << " " << B << endl;
    vector <long long> ostatki(10, 0);
    if (checkB(B)) {
        long long result = randomPrimeNumber(primeNumbers, A, B);
        cout << "going upper, boss, find: " <<  A <<  " " <<  result << " " << B << endl;
        return result;
    }
    q_A = (long long) (ceil(sqrt(B)));
    alpha = double(A+B-1)/double(2*A);
    k_1 = (long long) ceil(double(A)/double(q_A));
    k_2 = (long long) floor(double((B-1))/(double(q_A)/alpha));
    q_B = (long long) floor(alpha * q_A);
    k_n = k_2;
L2:
    q = findNumbers(primeNumbers, q_A, min(B,q_B));
    if (A < q && q < B) {
        cout << "going upper, boss, find: " <<  A <<  " " <<  q << " " << B << endl;
        return q;
    }
L4:
    //cout << "L4" << endl;
    if (k_n - k_1 - 1 <= 0) {
        k_n = k_2;
        goto L2; //если границы схопнулись, то идем пытать счастье с новым q
    }
    //cout << "k1: " << k_1 <<  " kn: " << k_n << endl;
    k = k_1 + 1 + rand() % (k_n - k_1 - 1);
    /*если к не из промежутка, то и простое число р не из промежутка*/
    if (k % 2 != 0)
        k = k - 1;
    //cout << "k1: " << k_1 << " k: " << k << " kn: " << k_n << endl;
    k_s = k_n;
    k_n = k;
    p = k * q + 1;
    // cout << p << endl;
    /*
     в какой-то момент число р стало больше границы B, 
     в этот момент возвращаемся и генерируем к из промежутка к_1 до к текущего
    */
    /*
     однако никто не гарантирует, что мы найдем такое р
     следовательно может возникунуть деление на 0
     следовательно, еще раз генерим q
     */
    
    
    for (long long i = 0; i < 10; ++i){
        ostatki[i] = p % primeNumbers[i+1];
    }
L6:
    //cout << "L6" << endl;
    k = k + 2;
    p = p + 2*q;
    
    for (long long i = 0; i < 10; ++i){
        ostatki[i] = (ostatki[i] + 2)%primeNumbers[i+1];
    }
    
    if (k > k_s || p > B) {
        // cout << p << " " << B << endl;
        goto L4;
    }
    
    for (long long  i = 0; i < 10; ++i){
        if (ostatki[i] == 0) {
            goto L6;
        }
    }
    
    if (!(MillerRabin(p))) {
        // cout << "lol: " << p; //<< " trus: " << trustMe(p) << endl;
        goto L6;
    }
    
    counter = 10;
L11:
    // cout << "L11" << endl;
    counter--;
    long long  a = abs(rand()) % B;
    long long  t = (myPowMod(a, k, p) - 1 + p)% p;
    long long  tt = myPowMod(a, p - 1, p);
    if ((gcd(t, p)) == 1)
        if ((tt % p) == 1){
            cout << "going upper, boss, find: " <<  A <<  " " <<  p << " " << B << endl;
            return p;
        }
    if (counter == 0)
        goto L6;
    else
        goto L11;
}

long long mainAlgorythm(){
    vector < long long > table = tableOfPrimeNumbers(65546);
    auto p = input();
    long long A = p.first;
    long long B = p.second;
    start_time =  clock();
    while (checkInput(A,B) == false) {
        p = input();
        A = p.first;
        B = p.second;
    }
    return findNumbers(table, A, B);
}

int main() {
//    srand(179);
    srand(time(0));
    long long ans = mainAlgorythm();
    cout << "The prime number is :" << ans << endl;
    cout << trustMe(ans) << endl;
    end_time = clock();
    
    cout << "runtime = " << (end_time - start_time)/1000.0 << endl; // время работы программы
    //cout << makePrimeNumber(7,12) << endl;
    return 0;
}
