#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <climits>

using namespace std;

const int NMAX = 40000000;

typedef bool*  boolArrayPtr;
typedef int* intArrayPtr;
typedef vector<int>* intVectorPtr;
typedef intVectorPtr* intVectorArrayPtr;

 intArrayPtr primeListSieve(bool sieve[], int nMax, int &nPrimes);
// Precondition:  sieve is an int array of size nMax that has been initialized
// so that all the values are true.  primes is an empty int vector. nMax is the
// maximum size of the sieve.
// Postcondition: sieve is a prime number sieve for ints up to nMax, primes is a
// list of all the primes up to but not including nMax

int concatNums(int a, int b);
// Precondition: a and b are positive ints
// Postcondition: return 'concated' result ab.  For example concatNums(3,7) returns 37 while
// concatNums(7,3) returns 73

bool isPrimePair(bool sieve[], int a, int b);
// Precondition sieve is a prime number sieve,; a and b are primes such that the
// 'concated' values ab and ba are less than the size of the sieve
// Postcondition: if a and b are prime pairs returns true, otherwise returns false
// a and b constitute a prime pair if 'concated' ab is prime and ba is prime

intVectorArrayPtr generatePrimePairLists(bool isPrime[], intArrayPtr pList, int nPrimes);
// Precondition: isPrime is prime sieve of size NMAX, pList is a pointer to an array of length nPrimes
// that represents the prime numbers generated from the sieve
// Postcondition: returns a pointer to an array of length NMAX of vector<int> pointers which point to the
// lists of prime pairs associated with the different indicies.

int main()
{
    int nPrimes;

    boolArrayPtr isPrime = new bool[NMAX];
    fill_n(isPrime, NMAX, true);

    intArrayPtr pList = primeListSieve(isPrime, NMAX, nPrimes);
    intVectorArrayPtr primePairLists = generatePrimePairLists(isPrime, pList, nPrimes);


    int iLimit = 3999;
    int num = 0;
    for(int j = 0; pList[j] < iLimit ; j++)
    {
        if(primePairLists[pList[j]]->size() > 4)
        {
            cout << pList[j] << "  "  << primePairLists[pList[j]]->size() << endl;

            num++;

//            for(int i = 0; i < primePairLists[pList[j]]->size(); i++)
            vector<int>::iterator it;
            vector<int>::iterator itbegin = primePairLists[pList[j]]->begin();
            //cout << *itbegin << endl;
            vector<int>::iterator itend = primePairLists[pList[j]]->end();
            //cout << *(itend - 1) << endl;
            for( it = itbegin; it != itend; ++it)
            {
                if(primePairLists[*it]->size() > 4)
                    cout << *it << endl;
            }

//                cout << (*primePairLists[pList[j]])[*it] << endl;
        }
    }

    cout << num << endl;

    return 0;
}

intArrayPtr primeListSieve(bool sieve[], int nMax, int &nPrimes)
{
    vector<int> primeVector;
    sieve[0] = false;
    sieve[1] = false;

    // create sieve
    for(int i = 2; i < static_cast<int>(ceil(sqrt(NMAX))); i++)
    {
        if(sieve[i])
        {
            for(int j = 2*i; j < NMAX; j += i)
            {
                sieve[j] = false;
            }
        }
    }

    // create primes list
    for(int i = 0; i < NMAX; i++)
    {
        if(sieve[i])
            primeVector.push_back(i);
    }

    nPrimes = primeVector.size();
    intArrayPtr primes = new int[nPrimes];
    copy(primeVector.begin(), primeVector.end(), primes);
    return primes;
}

int concatNums(int a, int b)
{
    int exp = static_cast<int>(ceil(log10(b)));
    return static_cast<int>(a * pow(10, exp))+ b;
}

bool isPrimePair(bool isPrime[], int a, int b)
{

    return isPrime[concatNums(a, b)] && isPrime[concatNums(b, a)];
}

intVectorArrayPtr generatePrimePairLists(bool isPrime[], intArrayPtr pList, int nPrimes)
{
    intVectorArrayPtr primePairLists = new intVectorPtr[NMAX];
    fill_n(primePairLists, NMAX, nullptr);

    int iLimit = 4000;

    for(int i = 0; pList[i] < iLimit - 1; i++)
    {
        if(primePairLists[pList[i]] == nullptr)
            primePairLists[pList[i]] = new vector<int>();
        primePairLists[pList[i]]->push_back(pList[i]);

//        cout << i << "  " << pList[i] << endl;

        int j = i+1;


        while((concatNums(pList[i], pList[j]) < NMAX) && (concatNums(pList[j], pList[i]) < NMAX))
        {
//            if(pList[i] == 109 && pList[j] > 1000 && pList[j] < 100000)
//                cout << pList[i] << "  " << pList[j] << endl;


            if(isPrimePair(isPrime, pList[i], pList[j]))
            {
//                if(pList[i] == 3 && pList[j] < 30000)
//                    cout << pList[i] << "  " << pList[j] << endl;

                if (primePairLists[pList[j]] == nullptr)
                    primePairLists[pList[j]] = new vector<int>();

                primePairLists[pList[i]]->push_back(pList[j]);
                primePairLists[pList[j]]->push_back(pList[i]);
            }

            j++;

        }
    }

    return primePairLists;
}
