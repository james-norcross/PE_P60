//Author: James Norcross
//Date: 1/2/16
//Purpose: solution of ProjectEuler.org problem 60
//Description:  a and b are prime pairs if
//                  a is prime
//                  b is prime
//                  ab is prime
//                  ba is prime
// Note: ab is 'concatination' of a and b.  For example is a is 3 and b is 7 then ab is 37
//The problem is to find the set of 5 primes p1, p2, p3, p4, p5 for which all p's are prime pairs of one another
// and the sum of the 5 p's is the minimized

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

const int NMAX = 100000000;
const int PP_LIMIT = 10000;

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
    bool done0, done1, done2, done3, done4;


    boolArrayPtr isPrime = new bool[NMAX];
    fill_n(isPrime, NMAX, true);

    intArrayPtr pList = primeListSieve(isPrime, NMAX, nPrimes);
    cout << "Created prime sieve and list" << endl;
    intVectorArrayPtr primePairLists = generatePrimePairLists(isPrime, pList, nPrimes);
    cout << "Created prime pairs lists" << endl;


    //step through list of primes with 5 markers to track candidates for 5 elements in set of prime pairs
    int m[] = {1,1,1,1,1};          // markers to track where each set element is in primes pairs list

    done0 = false;

    // loop for first element
    while(!done0)
    {
        m[1] = m[0] + 1;
        done1 = false;

        //loop for second element
        while(!done1)
        {

            //if have two of the five elements in the set then step to trying to find 3rd element
            if((primePairLists[pList[m[1]]] != nullptr) && binary_search(primePairLists[pList[m[0]]]->begin(), primePairLists[pList[m[0]]]->end(), pList[m[1]]))
            {

                m[2] = m[1]+1;
                done2 = false;

                // loop for 3rd element
                while(!done2)
                {

                    //if have found three of the five elements step to trying to find the forth
                    if((primePairLists[pList[m[2]]] != nullptr)
                    && binary_search(primePairLists[pList[m[0]]]->begin(), primePairLists[pList[m[0]]]->end(), pList[m[2]])
                    && binary_search(primePairLists[pList[m[1]]]->begin(), primePairLists[pList[m[1]]]->end(), pList[m[2]]))
                    {

                        m[3] = m[2]+1;
                        done3 = false;

                        //loop for 4th element
                        while(!done3)
                        {

                            // if have found four of the five elements step to trying to find the fifth
                            if((primePairLists[pList[m[3]]] != nullptr)
                            && binary_search(primePairLists[pList[m[0]]]->begin(), primePairLists[pList[m[0]]]->end(), pList[m[3]])
                            && binary_search(primePairLists[pList[m[1]]]->begin(), primePairLists[pList[m[1]]]->end(), pList[m[3]])
                            && binary_search(primePairLists[pList[m[2]]]->begin(), primePairLists[pList[m[2]]]->end(), pList[m[3]]))
                            {

                                m[4] = m[3] + 1;
                                done4 = false;

                                // loop for 5th element
                                while(!done4)
                                {
                                    if((primePairLists[pList[m[3]]] != nullptr)
                                    && binary_search(primePairLists[pList[m[0]]]->begin(), primePairLists[pList[m[0]]]->end(), pList[m[4]])
                                    && binary_search(primePairLists[pList[m[1]]]->begin(), primePairLists[pList[m[1]]]->end(), pList[m[4]])
                                    && binary_search(primePairLists[pList[m[2]]]->begin(), primePairLists[pList[m[2]]]->end(), pList[m[4]])
                                    && binary_search(primePairLists[pList[m[3]]]->begin(), primePairLists[pList[m[3]]]->end(), pList[m[4]]))
                                    {
                                        cout << pList[m[0]] << "   " << pList[m[1]] << "  " << pList[m[2]] << "  " << pList[m[3]] << "  " << pList[m[4]] << endl;
                                    }

                                    m[4]++;

                                    // if reach limit for marker 4, increment marker 3 and return to loop 3
                                    if(m[4] > nPrimes -2)
                                    {
                                        done4 = true;
                                        m[3]++;
                                    }

                                }
                            }

                            m[3]++;

                            // if reach limit for marker 3, increment marker 2 and return to loop 2
                            if(pList[m[3]] > PP_LIMIT)
                            {
                                done3 = true;
                                m[2]++;
                            }

                        }
                    }

                    m[2]++;

                    // if reach limit for marker 2, increment marker 1 and return to loop 1
                    if(pList[m[2]] > PP_LIMIT)
                    {
                        done2 = true;
                        m[1]++;
                    }
                }
            }

            m[1]++;

            // if reach limit for marker 1, increment marker 0 and break to loop 0
            if (pList[m[1]] > PP_LIMIT)
            {
                done1 = true;
                m[0]++;
            }

        }

        // if reach limit for marker 0 have completed search for set of 5 prime pairs
        if (pList[m[0]] > PP_LIMIT)
        {
            done0 = true;
        }
    }


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
    return static_cast<int>(ceil(a * pow(10, exp))) + b;
}

bool isPrimePair(bool isPrime[], int a, int b)
{
    return isPrime[concatNums(a, b)] && isPrime[concatNums(b, a)];
}

intVectorArrayPtr generatePrimePairLists(bool isPrime[], intArrayPtr pList, int nPrimes)
{

    intVectorArrayPtr primePairLists = new intVectorPtr[NMAX];
    fill_n(primePairLists, NMAX, nullptr);

    //NOTE: use PP_LIMIT because the only prime pair lists that can be complete are those for which
    // concated values ab and ba are less than the size of the prime sieve NMAX.  Can include values
    // greater than this limit in prime pairs list by letting the while loop limit the concated values
    // this will include some candidate prime pairs with values > PP_LIMIT but will only check these in
    // determining last element of set of prime pairs.


    for(int i = 0; pList[i] < PP_LIMIT - 1; i++)
    {
        if(primePairLists[pList[i]] == nullptr)
            primePairLists[pList[i]] = new vector<int>();
        primePairLists[pList[i]]->push_back(pList[i]);

        int j = i+1;

        while((concatNums(pList[i], pList[j]) < NMAX) && (concatNums(pList[j], pList[i]) < NMAX))
        {
            if(isPrimePair(isPrime, pList[i], pList[j]))
            {

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
