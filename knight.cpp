#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

bool isPrime(const int num)
{
    if (num <= 1)
        return false;

    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return false;

    return true;
}

int nextFib(int currentHP)
{
    int num1 = 1;
    int num2 = 1;

    while (num1 + num2 < currentHP)
    {
        std::swap(num1, num2);
        num2 = num1 + num2;
    }

    return num2;
}

int isMountain(int nums[], int size)
{
    int left = 0;
    int right = size - 1;

    while (left < right && nums[left] < nums[left + 1] && nums[right - 1] > nums[right])
    {
        left++;
        right--;
    }

    while (left < right && nums[left] < nums[left + 1])
        left++;

    while (left < right && nums[right - 1] > nums[right])
        right--;

    return left == right ? left : -3;
}

int countUnique(int a, int b, int c)
{
    if (a == b && b == c)
        return 1;
    if (a == b || a == c || b == c)
        return 2;
    return 3;
}

void adventureToKoopa(string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue)
{
    ifstream file(file_input);
    string inputLine1, inputLine2, inputLine3;
    getline(file, inputLine1);
    getline(file, inputLine2);
    getline(file, inputLine3);

    // Read line 1 input
    stringstream stats(inputLine1);
    stats >> HP >> level >> remedy >> maidenkiss >> phoenixdown;

    // Read line 3 input
    string file1, file2, file3;
    istringstream files(inputLine3);
    getline(files, file1, ',');
    getline(files, file2, ',');
    getline(files, file3, ',');

    // Initialize
    bool isAthur = HP == 999;
    bool isLancelot = isPrime(HP) && !isAthur;
    bool isKnight = !isAthur && !isLancelot;

    int maxHP = HP;
    int i = 1;
    int minis = 0;
    int frogs = 0;
    int oldLevel = -1;
    int asceplius = 0;
    int merlin = 0;
    rescue = -1;

    // Start running each event by reading each event number
    istringstream journey(inputLine2);
    string eventNum;

    getline(journey, eventNum, ' ');

    while (rescue == -1)
    {
        int num = eventNum.length() < 3 ? atoi(eventNum.c_str()) : 13;
        // cout << "eventNum: " << eventNum << "minis: " << minis << endl;
        int oldHP = HP;
        if (num == 0)
            rescue = 1;
        else if (num <= 5 && num >= 1)
        {
            int b = i % 10;
            int levelOpponent = i > 6 ? (b > 5 ? b : 5) : b;
            int baseDamage[] = { 10, 15, 45, 75, 95 };
            if (isAthur || isLancelot || level > levelOpponent)
            {
                level++;
                level = min(level, 10);
            }
            else if (level == levelOpponent)
            {

            }
            else
            {
                HP -= baseDamage[num - 1] * levelOpponent;
            }
        }
        else if (num == 6)
        {
           
            if (!(minis || frogs))
            {

                int b = i % 10;
                int levelOpponent = i > 6 ? (b > 5 ? b : 5) : b;
                
                if (isAthur || isLancelot || level > levelOpponent)
                    level = min(10, level + 2);
               
                else if (level < levelOpponent)
                {
                    remedy -= 1;

                    if (remedy < 0)
                    {
                        remedy = 0;
                        minis = 4;
                        HP = HP <= 5 ? 1 : HP / 5;

                    }
                    

                    
                }
            }
        }
        else if (num == 7)
        {
            if (!(minis || frogs))
            {
                int b = i % 10;
                int levelOpponent = i > 6 ? (b > 5 ? b : 5) : b;

                if (isAthur || isLancelot || level > levelOpponent)
                    level = min(10, level + 2);
                else if (level == levelOpponent)
                {
                }
                else
                {
                    if (maidenkiss > 0)
                        maidenkiss -= 1;
                    else if (maidenkiss <= 0)
                    {
                        maidenkiss = 0;
                        frogs = 4;

                        oldLevel = level;
                        level = 1;
                    }
                }
            }
        }
        else if (num == 11)
        {
            int n1 = (((level + phoenixdown) % 5) + 1) * 3;
            int s1 = 0;
            for (int n = 99; n1 != 0; n1--, n -= 2)
                s1 += n;

            HP = min(maxHP, HP + (s1 % 100));

            if (isPrime)
                HP++;

            while (!isPrime(HP))
            {
                HP++;
            }
            if (HP >= maxHP)
            {
                HP = maxHP;
            }
        }
        else if (num == 12)
        {
            HP = HP == 1 ? HP : nextFib(HP);
        }
        else if (num == 13)
        {
            // read file mush_ghost
            ifstream mushGhost(file1);
            string msLine1, msLine2;
            getline(mushGhost, msLine1);
            getline(mushGhost, msLine2);

            // read mushrooms
            string ms = eventNum.substr(2, string::npos);

            for (char m : ms)
            {
                int nums[100] = {};
                int numLine = 0;
                string n;
                istringstream ssms(msLine2);

                while (getline(ssms, n, ','))
                    nums[numLine++] = stoi(n);

                int msNum = m - '0';

                if (msNum == 1)
                {
                    int minI = 0;
                    int maxI = 0;
                    for (int i = 1; i < numLine; i++)
                    {
                        if (nums[i] <= nums[minI])
                            minI = i;
                        if (nums[i] >= nums[maxI])
                            maxI = i;
                    }
                    HP -= (minI + maxI);

                }
                if (msNum == 2)
                {
                    int peakAt = isMountain(nums, numLine);
                    int peakVal = peakAt == -3 ? -2 : nums[peakAt];

                    HP -= (peakAt + peakVal);
                    
                }
                if (msNum == 3)
                {
                    for (int j = 0; j < numLine; j++)
                    {
                        if (nums[j] < 0)
                            nums[j] = -nums[j];

                        nums[j] = (17 * nums[j] + 9) % 257;
                    }

                    int minI = 0;
                    int maxI = 0;
                    for (int i = 1; i < numLine; i++)
                    {
                        if (nums[i] < nums[minI])
                            minI = i;
                        if (nums[i] > nums[maxI])
                            maxI = i;
                    }

                    HP -= (minI + maxI);

                }
                if (msNum == 4)
                {
                    int maxV = -5;
                    int maxI = -7;

                    for (int j = 0; j < numLine; j++)
                    {
                        if (nums[j] < 0)
                            nums[j] = -nums[j];

                        nums[j] = (17 * nums[j] + 9) % 257;
                    }

                    int first = nums[0];
                    int second = nums[1];
                    int third = nums[2];

                    int unique = countUnique(first, second, third);

                    if (numLine < 3 || unique == 1)
                        ;
                    else
                    {
                        int max3 = max(first, max(second, third));
                        if (unique == 2)
                        {
                            maxI = first == max3 ? 0 : 1;
                            maxV = nums[maxI];
                        }
                        else if (unique == 3)
                        {
                            int min3 = min(first, min(second, third));

                            if (!(first == max3 || first == min3))
                            {
                                maxV = first;
                                maxI = 0;
                            }
                            if (!(second == max3 || second == min3))
                            {
                                maxV = second;
                                maxI = 1;
                            }
                            if (!(third == max3 || third == min3))
                            {
                                maxV = third;
                                maxI = 2;
                            }
                        }
                    }

                    HP -= (maxI + maxV);

                }
                if (HP <= 0 && !phoenixdown)
                    break;
                else if (HP <= 0 && phoenixdown)
                {
                    HP = maxHP;
                    phoenixdown -= 1;
                }
                else
                    HP = min(maxHP, HP);
            }
        }
        else if (num >= 15 && num <= 17)
        {
            if (num == 15)
                remedy = min(99, remedy + 1);
            if (num == 16)
                maidenkiss = min(99, maidenkiss + 1);
            if (num == 17)
                phoenixdown = min(99, phoenixdown + 1);
        }
        else if (num == 18)
        {
            if (!merlin)
            {
                merlin = 1;
                int countM = 0, countE = 0, countR = 0, countL = 0, countI = 0, countN = 0;

                ifstream merlinFile(file3);
                string merlinLine = "";

                while (getline(merlinFile, merlinLine))
                {
                    if (merlinLine.length() < 6)
                        continue;

                    if (merlinLine.find("merlin") != string::npos || merlinLine.find("Merlin") != string::npos)
                    {
                        HP = min(maxHP, HP + 3);
                        continue;
                    }

                    for (char c : merlinLine)
                    {
                        if (c == 'M' || c == 'm')
                            countM++;
                        if (c == 'E' || c == 'e')
                            countE++;
                        if (c == 'R' || c == 'r')
                            countR++;
                        if (c == 'L' || c == 'l')
                            countL++;
                        if (c == 'I' || c == 'l')
                            countI++;
                        if (c == 'N' || c == 'n')
                            countN++;
                    }

                    if (countM && countE && countR && countL && countI && countN)
                        HP = min(maxHP, HP + 2);
                    countM = 0;
                    countE = 0;
                    countR = 0;
                    countL = 0;
                    countI = 0;
                    countN = 0;
                }

            }
        }
        else if (num == 19)
        {
            if (!asceplius) {


                ifstream pack(file2);

                int r1 = 0;
                int c1 = 0;

                string t1, t2;

                getline(pack, t1);
                getline(pack, t2);

                r1 = stoi(t1);
                c1 = stoi(t2);

                for (int i = 0; i < r1; i++)
                {
                    string packLine;
                    getline(pack, packLine);

                    istringstream numbers(packLine);
                    for (int j = 0, ns = 0; j < c1 && ns < 3; j++)
                    {
                        int n = 0;
                        numbers >> n;
                        if (n == 16)
                            remedy = min(99, remedy + 1);
                        if (n == 17)
                            maidenkiss = min(99, maidenkiss + 1);
                        if (n == 18)
                            phoenixdown = min(99, phoenixdown + 1);

                        if (n == 16 || n == 17 || n == 18)
                            ns += 1;
                    }
                }

                asceplius = 1;
            }

        }
        else if (num == 99)
        {
            if (isAthur)
                continue;
            if (isLancelot && level < 8)
                rescue = 0;
            if (isKnight && level < 10)
                rescue = 0;
        }

        i += 1;

        if (!getline(journey, eventNum, ' '))
            rescue = 1;

        if (HP <= 0)
        {
            phoenixdown -= 1;

            if (phoenixdown < 0)
            {
                phoenixdown = 0;
                rescue = 0;
            }
            else
            {
                HP = maxHP;
                minis = 0;
                frogs = 0;
                oldLevel = -1;
            }
        }


        if (minis && remedy)
        {
            minis = 1;
            remedy -= 1;
        }

        if (frogs && maidenkiss)
        {
            frogs = 1;
            maidenkiss -= 1;
        }

        if (minis - 1 == 0 && rescue != 0)
        {
            HP = HP*5;
        }

        if (frogs - 1 == 0 && rescue != 0)
        {
            level = oldLevel;
            oldLevel = -1;
        }

        if (minis)
            minis -= 1;
        if (frogs)
            frogs -= 1;
        
        HP = min(maxHP, HP);

        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    }
}