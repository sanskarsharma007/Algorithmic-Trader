#include "receiver.h"
#include <vector>
#include <sstream>
#include <string>
#include <unistd.h>
#include <algorithm>

bool isInteger(std::string str)
{
    for (char c : str)
    {
        if (std::isdigit(c))
        {
            return true;
        }
    }
    return false;
}

int findLastIndex(const std::vector<std::string> &myVector, std::string elementToFind)
{
    for (int i = myVector.size() - 1; i >= 0; i--)
    {
        if (myVector[i] == elementToFind)
        {
            return i;
        }
    }

    return -1;
}

bool isarbitrage(std::vector<std::vector<std::string>> subsetString, std::vector<std::vector<int>> subsetInt)
{
    for (int i = 0; i < subsetString.size(); i++)
    {
        std::vector<std::string> differentStockWithName;
        std::vector<int> differentStockWithQuantity;
        for (int j = 0; j < subsetString[i].size(); j++)
        {
            std::string stockName = subsetString[i][j];
            int stockQuantity = subsetInt[i][j];
            bool found = false;
            for (int k = 0; k < differentStockWithQuantity.size(); j++)
            {
                if (differentStockWithName[k] == stockName)
                {
                    differentStockWithQuantity[k] += stockQuantity;
                    found = true;
                }
            }

            if (!found)
            {
                differentStockWithName.push_back(stockName);
                differentStockWithQuantity.push_back(stockQuantity);
            }
        }
        for (int quantity : differentStockWithQuantity)
        {
            if (quantity != 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool hasMultipleConsecutiveIntegerWords(std::string str)
{
    std::istringstream iss(str);
    std::string word;
    int consecutiveIntegerCount = 0;

    while (iss >> word)
    {
        if (isInteger(word))
        {
            consecutiveIntegerCount++;
            if (consecutiveIntegerCount > 2)
            {
                return true;
            }
        }
        else
        {
            consecutiveIntegerCount = 0;
        }
    }

    return false;
}

int IndexMultipleConsecutiveInteger(std::string str)
{
    std::istringstream iss(str);
    std::string word;
    int consecutiveIntegerCount = 0;
    int i = 0;
    while (iss >> word)
    {
        if (isInteger(word))
        {
            consecutiveIntegerCount++;
            i++;
            if (consecutiveIntegerCount > 2)
            {
                break;
            }
        }
        else
        {
            consecutiveIntegerCount = 0;
            i++;
        }
    }
    return i - 1;
}

int lineInMessage(std::string str)
{
    int lincount = 0;
    std::string stocks;
    std::istringstream iss(str);
    while (std::getline(iss, stocks, '#'))
    {
        if (stocks == "$")
        {
            break;
        }
        lincount++;
    }
    return lincount;
}

int countWords(std::string str)
{
    int count = 0;
    bool inWord = false;

    for (char c : str)
    {
        if (isspace(c))
        {
            inWord = false;
        }
        else if (!inWord)
        {
            inWord = true;
            count++;
        }
    }
    return count;
}

bool elementExists(const std::vector<std::string> &v, const std::string &element)
{
    for (auto it : v)
    {
        if (it == element)
        {
            return true;
        }
    }
    return false;
}

int findElementIndex(const std::vector<std::string> &vec, const std::string &element)
{

    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == element)
        {
            return i;
        }
    }
    return -1;
}

bool stocksEqual(std::vector<std::string> v1, std::vector<std::string> v2, std::vector<int> v3, std::vector<int> v4)
{
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::sort(v3.begin(), v3.end());
    std::sort(v4.begin(), v4.end());
    if (v1 == v2 && v3 == v4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void generatePowerSetString(const std::vector<std::vector<std::string>> &vvs, std::vector<std::vector<std::string>> &finalvec, std::vector<std::string> &current, int index)
{

    if (index == vvs.size())
    {
        finalvec.push_back(current);
        return;
    }

    generatePowerSetString(vvs, finalvec, current, index + 1);
    std::vector<std::string> temp;
    temp = current;
    current.insert(current.end(), vvs[index].begin(), vvs[index].end());
    generatePowerSetString(vvs, finalvec, current, index + 1);
    current = temp;
}

void generatePowerSetInt(const std::vector<std::vector<int>> &vvs, std::vector<std::vector<int>> &finalvec, std::vector<int> &current, int index)
{

    if (index == vvs.size())
    {
        finalvec.push_back(current);
        return;
    }

    generatePowerSetInt(vvs, finalvec, current, index + 1);
    std::vector<int> temp;
    temp = current;
    current.insert(current.end(), vvs[index].begin(), vvs[index].end());
    generatePowerSetInt(vvs, finalvec, current, index + 1);
    current = temp;
}

int main()
{
    std::vector<std::string> tradedStockNameList;
    std::vector<int> tradedStockPriceList;
    std::vector<char> tradedStockType;
    std::vector<std::string> activeStockNameList;
    std::vector<int> activeStockPriceList;
    std::vector<char> activeStockType;
    std::vector<std::string> stockNameList;
    std::vector<int> stockPriceList;
    std::vector<std::pair<bool, int>> visited;
    std::vector<int> price;
    std::vector<int> stockQuantityList;
    std::vector<int> linearCombination;
    std::vector<int> totalStockQuantityList;
    std::vector<int> updateStockQuantity;
    std::vector<char> types;
    Receiver rcv;
    sleep(5);
    std::string message = rcv.readIML();

    std::istringstream iss(message);
    std::string stocks;
    int lines = lineInMessage(message);
    int totalLine = 1;
    int totalPrice = 0;
    while (std::getline(iss, stocks, '#'))
    {
        if (stocks == "$")
        {
            break;
        }
        std::istringstream stock(stocks);
        int totalWords = countWords(stocks);
        bool multipleConsecutiveIntegers = hasMultipleConsecutiveIntegerWords(stocks);
        // Part 1
        if (totalWords == 3)
        {
            std::string stockName;
            int stockPrice;
            std::string type;
            stock >> stockName >> stockPrice >> type;
            if (elementExists(activeStockNameList, stockName) && elementExists(tradedStockNameList, stockName))
            {
                int index = findLastIndex(activeStockNameList, stockName);
                if (activeStockType[index] != type[0] && stockPrice == activeStockPriceList[index])
                {
                    activeStockNameList.erase(activeStockNameList.begin() + index);
                    activeStockPriceList.erase(activeStockPriceList.begin() + index);
                    activeStockType.erase(activeStockType.begin() + index);
                    std::cout << "No Trade" << std::endl;
                }

                else
                {
                    if (stockPrice == activeStockPriceList[index])
                    {
                        std::cout << "No Trade" << std::endl;
                    }
                    else
                    {
                        int index_ = findLastIndex(tradedStockNameList, stockName);
                        if (type[0] == 's')
                        {
                            if (tradedStockPriceList[index_] > stockPrice)
                            {
                                std::cout << stockName << " " << stockPrice << " " << 'b' << std::endl;
                                tradedStockNameList.push_back(stockName);
                                tradedStockPriceList.push_back(stockPrice);
                                tradedStockType.push_back(type[0]);
                            }
                            else
                            {
                                std::cout << "No Trade" << std::endl;

                                activeStockPriceList[index] = stockPrice;
                                activeStockType[index] = type[0];
                            }
                        }
                        else
                        {
                            if (tradedStockPriceList[index_] < stockPrice)
                            {
                                std::cout << stockName << " " << stockPrice << " " << 's' << std::endl;
                                tradedStockNameList.push_back(stockName);
                                tradedStockPriceList.push_back(stockPrice);
                                tradedStockType.push_back(type[0]);
                            }
                            else
                            {
                                std::cout << "No Trade" << std::endl;

                                activeStockPriceList[index] = (stockPrice);
                                activeStockType[index] = (type[0]);
                            }
                        }
                    }
                }
            }
            else if (!elementExists(activeStockNameList, stockName) && elementExists(tradedStockNameList, stockName))
            {
                int index = findLastIndex(tradedStockNameList, stockName);
                if (type[0] == 's')
                {
                    if (tradedStockPriceList[index] > stockPrice)
                    {
                        std::cout << stockName << " " << stockPrice << " " << 'b' << std::endl;
                        tradedStockNameList.push_back(stockName);
                        tradedStockPriceList.push_back(stockPrice);
                        tradedStockType.push_back(type[0]);
                    }
                    else
                    {
                        std::cout << "No Trade" << std::endl;
                        activeStockNameList.push_back(stockName);
                        activeStockPriceList.push_back(stockPrice);
                        activeStockType.push_back(type[0]);
                    }
                }
                else
                {
                    if (tradedStockPriceList[index] < stockPrice)
                    {
                        std::cout << stockName << " " << stockPrice << " " << 's' << std::endl;
                        tradedStockNameList.push_back(stockName);
                        tradedStockPriceList.push_back(stockPrice);
                        tradedStockType.push_back(type[0]);
                    }
                    else
                    {
                        std::cout << "No Trade" << std::endl;
                        activeStockNameList.push_back(stockName);
                        activeStockPriceList.push_back(stockPrice);
                        activeStockType.push_back(type[0]);
                    }
                }
            }
            else if (elementExists(activeStockNameList, stockName) && !elementExists(tradedStockNameList, stockName))
            {
                int index = findLastIndex(activeStockNameList, stockName);
                if (activeStockType[index] != type[0] && stockPrice == activeStockPriceList[index])
                {
                    activeStockNameList.erase(activeStockNameList.begin() + index);
                    activeStockPriceList.erase(activeStockPriceList.begin() + index);
                    activeStockType.erase(activeStockType.begin() + index);
                    std::cout << "No Trade" << std::endl;
                }

                else
                {
                    if (type[0] == 's')
                    {
                        if (activeStockPriceList[index] <= stockPrice)
                        {
                            std::cout << "No Trade";
                        }
                        else
                        {
                            tradedStockNameList.push_back(stockName);
                            tradedStockPriceList.push_back(stockPrice);
                            tradedStockType.push_back(type[0]);
                            std::cout << stockName << " " << stockPrice << " ";
                            std::cout << 'b' << std::endl;
                        }
                    }
                    else if (type[0] = 'b')
                    {
                        if (activeStockPriceList[index] >= stockPrice)
                        {
                            std::cout << "No Trade";
                        }
                        else
                        {
                            tradedStockNameList.push_back(stockName);
                            tradedStockPriceList.push_back(stockPrice);
                            tradedStockType.push_back(type[0]);
                            std::cout << stockName << " " << stockPrice << " ";
                            std::cout << 's' << std::endl;
                        }
                    }
                }
            }
            else
            {
                tradedStockNameList.push_back(stockName);
                tradedStockPriceList.push_back(stockPrice);
                tradedStockType.push_back(type[0]);
                std::cout << stockName << " " << stockPrice << " ";
                if (type[0] == 's')
                {
                    std::cout << 'b' << std::endl;
                }
                else
                {
                    std::cout << 's' << std::endl;
                }
            }
        }
        // Part2

        else if (!(multipleConsecutiveIntegers))
        {
            for (int i = 0; i < totalWords; i++)
            {
                if (i % 2 == 0 && i < totalWords - 2)
                {
                    std::string stockName;
                    stock >> stockName;
                    stockNameList.push_back(stockName);
                }
                else if (i % 2 != 0 && i < totalWords - 2)
                {
                    int stockQuantity;
                    stock >> stockQuantity;
                    stockQuantityList.push_back(stockQuantity);
                }
                else if (i == totalWords - 2)
                {
                    int price;
                    stock >> price;
                    stockPriceList.push_back(price);
                }
                else
                {
                    std::string type;
                    stock >> type;
                    types.push_back(type[0]);
                }
            }
            int n = 0;
            int size_ = linearCombination.size();
            if (size_ == 0)
            {
                n = stockNameList.size() - linearCombination.size();
            }
            else
            {
                int total = 0;
                for (int i = 0; i < size_; i++)
                {
                    total = total + linearCombination[i];
                }
                n = stockNameList.size() - total;
            }
            linearCombination.push_back(n);

            if (totalLine < lines)
            {
                std::vector<std::string> differentstocksWithQuantity;
                std::vector<int> differentstocksWithQuantityNumbers;
                int totalQuantity = 0;
                bool NoTrade = true;
                int i = 0;
                int k = 0;
                int totalCombiantion = 0;
                int linesize = stockPriceList.size();
                for (auto linear : linearCombination)
                {
                    totalCombiantion = totalCombiantion + linear;
                }
                std::vector<int> index;
                // for(int initial=0;initial<linesize;initial++){
                //     if(linearCombination[initial]==linearCombination[linesize-1]){
                //         int endIndex=totalCombiantion-linearCombination[linesize-1];
                //         int startIndex=totalCombiantion;
                //         for(int start=linesize-1;start>=initial;start--){
                //             startIndex=startIndex-linearCombination[start];
                //         }
                //         std::vector<std::pair<std::string,int>> endElements;
                //         std::vector<std::pair<std::string,int>> beginElements;
                //         for(int x=0;x<linearCombination[linesize-1];x++){
                //             endElements.push_back({stockNameList[endIndex+x],stockQuantityList[endIndex+x]});
                //         }
                //         for(int x=0;x<linearCombination[initial];x++){
                //             beginElements.push_back({stockNameList[startIndex+x],stockQuantityList[startIndex+x]});
                //         }
                //         std::sort(endElements.begin(),endElements.end());
                //         std::sort(beginElements.begin(),beginElements.end());
                //         if(beginElements==endElements){

                //             if(stockPriceList[initial]+stockPriceList[linesize-1]>0){
                //                 visited[initial].first=1;
                //                 visited[initial].second=linesize-1;
                //                 visited[linesize-1].first=1;
                //                 visited[linesize-1].second=initial;
                //                 if(price[linesize-1]>0){
                //                     if (stockPriceList[initial]+stockPriceList[linesize-1]>price[linesize-1]){
                //                         price[linesize-1]=stockPriceList[initial]+stockPriceList[linesize-1];
                //                     }
                //                 }
                //                 else{
                //                     price[linesize-1]=stockPriceList[initial]+stockPriceList[linesize-1];
                //                 }
                //             }
                //         }
                //     }
                // }

                while (k < stockNameList.size())
                {

                    for (int i = k; i < stockNameList.size(); i++)
                    {
                        std::string stockName = stockNameList[i];
                        int quantity = stockQuantityList[i];

                        bool found = false;
                        for (int j = 0; j < differentstocksWithQuantity.size(); j++)
                        {
                            if (differentstocksWithQuantity[j] == stockName)
                            {
                                if (types[size_ - 1] == 'b')
                                {
                                    differentstocksWithQuantityNumbers[j] += quantity;
                                    found = true;
                                }
                                else
                                {
                                    differentstocksWithQuantityNumbers[j] -= quantity;
                                    found = true;
                                }
                            }
                        }

                        if (!found)
                        {
                            differentstocksWithQuantity.push_back(stockName);
                            if (types[size_ - 1])
                            {
                                differentstocksWithQuantityNumbers.push_back(quantity);
                            }
                            else
                            {
                                differentstocksWithQuantityNumbers.push_back(-quantity);
                            }
                        }
                        totalQuantity += quantity;
                    }

                    bool allZero = true;
                    for (int quantity : differentstocksWithQuantityNumbers)
                    {
                        if (quantity != 0)
                        {
                            allZero = false;
                            break;
                        }
                    }

                    if (allZero)
                    {
                        NoTrade = false;

                        int initialPrice = 0;
                        if (i > 0)
                        {
                            initialPrice = k - linearCombination[i - 1] + 1;
                        }
                        for (int x = initialPrice; x < stockPriceList.size(); x++)
                        {
                            if (types[x] == 'b')
                            {
                                totalPrice = totalPrice + stockPriceList[x];
                            }
                            else
                            {
                                totalPrice = totalPrice - stockPriceList[x];
                            }
                        }
                        if (totalPrice <= 0)
                        {
                            std::cout << "No Trade" << std::endl;
                        }
                        else
                        {
                            int number = linearCombination.size();
                            int total = 0;

                            for (int x = 0; x < number; x++)
                            {
                                total += linearCombination[x];
                            }
                            int size = linearCombination.size();
                            int lastElement = linearCombination[size - 1];
                            int start = total - lastElement;
                            total = start;
                            for (int t = size - 1; t >= initialPrice; t--)
                            {
                                int b = linearCombination[t];
                                while (start == total)
                                {
                                    for (int s = 0; s < b; s++)
                                    {
                                        int a = start + s;
                                        std::cout << stockNameList[a] << " " << stockQuantityList[a] << " ";
                                    }
                                    if (types[t] == 'b')
                                    {

                                        std::cout << stockPriceList[t] << " "
                                                  << "s#" << std::endl;
                                    }
                                    else
                                    {
                                        std::cout << stockPriceList[t] << " "
                                                  << "b#" << std::endl;
                                    }

                                    if (t == initialPrice)
                                    {
                                        break;
                                    }
                                    start = start - linearCombination[t - 1];
                                }
                                total = total - linearCombination[t - 1];
                            }
                            std::cout << totalPrice << std::endl;

                            break;
                        }
                    }
                    differentstocksWithQuantity.clear();
                    differentstocksWithQuantityNumbers.clear();
                    k = k + linearCombination[i];
                    i++;
                }
                if (NoTrade)
                {
                    std::cout << "No Trade" << std::endl;
                }
                differentstocksWithQuantity.clear();
                differentstocksWithQuantityNumbers.clear();
            }

            else
            {
                std::vector<std::string> differentstocksWithQuantity;
                std::vector<int> differentstocksWithQuantityNumbers;
                int totalQuantity = 0;
                bool NoTrade = true;
                int i = 0;
                int k = 0;
                while (k < stockNameList.size() - 1)
                {
                    for (int i = k; i < stockNameList.size(); i++)
                    {
                        std::string stockName = stockNameList[i];
                        int quantity = stockQuantityList[i];

                        bool found = false;
                        for (int j = 0; j < differentstocksWithQuantity.size(); j++)
                        {
                            if (differentstocksWithQuantity[j] == stockName)
                            {
                                if (types[totalLine - 1] == 'b')
                                {
                                    differentstocksWithQuantityNumbers[j] += quantity;
                                }
                                else
                                {
                                    differentstocksWithQuantityNumbers[j] -= quantity;
                                }
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                        {
                            differentstocksWithQuantity.push_back(stockName);
                            if (types[totalLine - 1] == 'b')
                            {
                                differentstocksWithQuantityNumbers.push_back(quantity);
                            }
                            else
                            {
                                differentstocksWithQuantityNumbers.push_back(-quantity);
                            }
                        }

                        totalQuantity += quantity;
                    }

                    bool allZero = true;
                    for (int quantity : differentstocksWithQuantityNumbers)
                    {
                        if (quantity != 0)
                        {
                            allZero = false;
                            break;
                        }
                    }

                    if (allZero)
                    {

                        NoTrade = false;

                        int initialPrice = 0;
                        if (i > 0)
                        {
                            initialPrice = k - linearCombination[i - 1] + 1;
                        }
                        for (int x = initialPrice; x < stockPriceList.size(); x++)
                        {
                            if (types[x] == 'b')
                            {
                                totalPrice = totalPrice + stockPriceList[x];
                            }
                            else
                            {
                                totalPrice = totalPrice - stockPriceList[x];
                            }
                        }

                        if (totalPrice <= 0)
                        {
                            std::cout << "No Trade";
                        }
                        else
                        {

                            int number = linearCombination.size();
                            int total = 0;

                            for (int x = 0; x < number; x++)
                            {
                                total += linearCombination[x];
                            }
                            int size = linearCombination.size();
                            int lastElement = linearCombination[size - 1];
                            int start = total - lastElement;
                            total = start;
                            for (int t = size - 1; t >= initialPrice; t--)
                            {
                                int b = linearCombination[t];
                                while (start == total)
                                {
                                    for (int s = 0; s < b; s++)
                                    {
                                        int a = start + s;
                                        std::cout << stockNameList[a] << " " << stockQuantityList[a] << " ";
                                    }
                                    std::cout << stockPriceList[t] << " "
                                              << "s#" << std::endl;
                                    if (t == initialPrice)
                                    {
                                        break;
                                    }
                                    start = start - linearCombination[t - 1];
                                }
                                total = total - linearCombination[t - 1];
                            }
                            std::cout << totalPrice << std::endl;
                            break;
                        }
                    }
                    differentstocksWithQuantity.clear();
                    differentstocksWithQuantityNumbers.clear();
                    k = k + linearCombination[i];
                    i++;
                }
                if (NoTrade)
                {
                    std::cout << "No Trade" << std::endl;
                }
            }
        }
        // Part 3
        else
        {

            int index = IndexMultipleConsecutiveInteger(stocks);
            for (int i = 0; i < totalWords; i++)
            {
                if (i % 2 == 0 && i < index - 1)
                {
                    std::string stockName;
                    stock >> stockName;
                    stockNameList.push_back(stockName);
                }
                else if (i % 2 != 0 && i < index - 1)
                {
                    int stockQuantity;
                    stock >> stockQuantity;
                    stockQuantityList.push_back(stockQuantity);
                }
                else if (i == index - 1)
                {
                    int price;
                    stock >> price;
                    stockPriceList.push_back(price);
                }
                else if (i == index)
                {
                    int wholeQuantity;
                    stock >> wholeQuantity;
                    totalStockQuantityList.push_back(wholeQuantity);
                }
                else
                {
                    std::string type;
                    stock >> type;
                    types.push_back(type[0]);
                }
            }
            int n = 0;
            int size_ = linearCombination.size();
            if (size_ == 0)
            {
                n = stockNameList.size() - linearCombination.size();
            }
            else
            {
                int total = 0;
                for (int i = 0; i < size_; i++)
                {
                    total = total + linearCombination[i];
                }
                n = stockNameList.size() - total;
            }
            linearCombination.push_back(n);

            int linear = linearCombination.back();
            int i = linear;
            while (i > 0)
            {
                int total = totalStockQuantityList.back();
                int size = stockQuantityList.size();
                updateStockQuantity.push_back(stockQuantityList[size - i] * total);
                i--;
            }
            if (totalLine < lines)
            {
                std::vector<std::string> differentstocksWithQuantity;
                std::vector<int> differentstocksWithQuantityNumbers;

                int totalQuantity = 0;
                bool NoTrade = true;
                int i = 0;
                int k = 0;

                while (k < stockNameList.size())
                {
                    for (int i = k; i < stockNameList.size(); i++)
                    {
                        std::string stockName = stockNameList[i];
                        int quantity = updateStockQuantity[i];

                        bool found = false;
                        for (int j = 0; j < differentstocksWithQuantity.size(); j++)
                        {
                            if (differentstocksWithQuantity[j] == stockName)
                            {
                                if (types[size_ - 1] == 'b')
                                {
                                    differentstocksWithQuantityNumbers[j] += quantity;
                                }
                                else
                                {
                                    differentstocksWithQuantityNumbers[j] -= quantity;
                                }
                                found = true;
                            }
                        }

                        if (!found)
                        {
                            differentstocksWithQuantity.push_back(stockName);
                            if (types[size_ - 1] == 'b')
                            {
                                differentstocksWithQuantityNumbers.push_back(quantity);
                            }
                            else
                            {
                                differentstocksWithQuantityNumbers.push_back(-quantity);
                            }
                        }

                        totalQuantity += quantity;
                    }

                    bool allZero = true;
                    for (int quantity : differentstocksWithQuantityNumbers)
                    {
                        if (quantity != 0)
                        {
                            allZero = false;
                            break;
                        }
                    }

                    if (allZero)
                    {
                        NoTrade = false;
                        int totalPrice = 0;
                        int initialPrice = 0;
                        if (i > 0)
                        {
                            initialPrice = k - linearCombination[i - 1] + 1;
                        }
                        for (int x = initialPrice; x < stockPriceList.size(); x++)
                        {
                            if (types[x] == 'b')
                            {
                                totalPrice = totalPrice + (stockPriceList[x] * totalStockQuantityList[x]);
                            }
                            else
                            {
                                totalPrice = totalPrice - (stockPriceList[x] * totalStockQuantityList[x]);
                            }
                        }
                        if (totalPrice <= 0)
                        {
                            std::cout << "No Trade" << std::endl;
                        }
                        else
                        {
                            int number = linearCombination.size();
                            int total = 0;

                            for (int x = 0; x < number; x++)
                            {
                                total += linearCombination[x];
                            }
                            int size = linearCombination.size();
                            int lastElement = linearCombination[size - 1];
                            int start = total - lastElement;
                            total = start;
                            for (int t = size - 1; t >= initialPrice; t--)
                            {
                                int b = linearCombination[t];
                                while (start == total)
                                {
                                    for (int s = 0; s < b; s++)
                                    {
                                        int a = start + s;
                                        std::cout << stockNameList[a] << " " << stockQuantityList[a] << " ";
                                    }
                                    if (types[t] == 'b')
                                    {
                                        std::cout << stockPriceList[t] << " " << totalStockQuantityList[t] << " "
                                                  << "s#" << std::endl;
                                    }
                                    else
                                    {
                                        std::cout << stockPriceList[t] << " " << totalStockQuantityList[t] << " "
                                                  << "b#" << std::endl;
                                    }
                                    if (t == initialPrice)
                                    {
                                        break;
                                    }
                                    start = start - linearCombination[t - 1];
                                }
                                total = total - linearCombination[t - 1];
                            }
                            std::cout << totalPrice << std::endl;
                            break;
                        }
                    }
                    differentstocksWithQuantity.clear();
                    differentstocksWithQuantityNumbers.clear();
                    k = k + linearCombination[i];
                    i++;
                }
                if (NoTrade)
                {
                    std::cout << "No Trade" << std::endl;
                }
                differentstocksWithQuantity.clear();
                differentstocksWithQuantityNumbers.clear();
            }

            else
            {
                std::vector<std::string> differentstocksWithQuantity;
                std::vector<int> differentstocksWithQuantityNumbers;
                int totalQuantity = 0;
                bool NoTrade = true;
                int i = 0;
                int k = 0;
                while (k < stockNameList.size() - 1)
                {
                    for (int i = k; i < stockNameList.size(); i++)
                    {
                        std::string stockName = stockNameList[i];
                        int quantity = updateStockQuantity[i];

                        bool found = false;
                        for (int j = 0; j < differentstocksWithQuantity.size(); j++)
                        {
                            if (differentstocksWithQuantity[j] == stockName)
                            {
                                if (types[size_ - 1] == 'b')
                                {
                                    differentstocksWithQuantityNumbers[j] += quantity;
                                }
                                else
                                {
                                    differentstocksWithQuantityNumbers[j] -= quantity;
                                }
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                        {
                            differentstocksWithQuantity.push_back(stockName);
                            if (types[size_ - 1] == 'b')
                            {
                                differentstocksWithQuantityNumbers.push_back(quantity);
                            }
                            else
                            {
                                differentstocksWithQuantityNumbers.push_back(-quantity);
                            }
                        }

                        totalQuantity += quantity;
                    }

                    bool allZero = true;
                    for (int quantity : differentstocksWithQuantityNumbers)
                    {
                        if (quantity != 0)
                        {
                            allZero = false;
                            break;
                        }
                    }

                    if (allZero)
                    {

                        NoTrade = false;
                        int totalPrice = 0;
                        int initialPrice = 0;
                        if (i > 0)
                        {
                            initialPrice = k - linearCombination[i - 1] + 1;
                        }
                        for (int x = initialPrice; x < stockPriceList.size(); x++)
                        {
                            if (types[x] == 'b')
                            {
                                totalPrice = totalPrice + (stockPriceList[x] * totalStockQuantityList[x]);
                            }
                            else
                            {
                                totalPrice = totalPrice - (stockPriceList[x] * totalStockQuantityList[x]);
                            }
                        }

                        if (totalPrice <= 0)
                        {
                            std::cout << totalPrice << std::endl;
                            std::cout << "No Trade" << std::endl;
                        }
                        else
                        {

                            int number = linearCombination.size();
                            int total = 0;

                            for (int x = 0; x < number; x++)
                            {
                                total += linearCombination[x];
                            }
                            int size = linearCombination.size();
                            int lastElement = linearCombination[size - 1];
                            int start = total - lastElement;
                            total = start;
                            for (int t = size - 1; t >= initialPrice; t--)
                            {
                                int b = linearCombination[t];
                                while (start == total)
                                {
                                    for (int s = 0; s < b; s++)
                                    {
                                        int a = start + s;
                                        std::cout << stockNameList[a] << " " << stockQuantityList[a] << " ";
                                    }
                                    if (types[t] == 'b')
                                    {
                                        std::cout << stockPriceList[t] << " " << totalStockQuantityList[t] << " "
                                                  << "s#" << std::endl;
                                    }
                                    else
                                    {
                                        std::cout << stockPriceList[t] << " " << totalStockQuantityList[t] << " "
                                                  << "b#" << std::endl;
                                    }
                                    if (t == initialPrice)
                                    {
                                        break;
                                    }
                                    start = start - linearCombination[t - 1];
                                }
                                total = total - linearCombination[t - 1];
                            }
                            std::cout << totalPrice << std::endl;
                            break;
                        }
                    }
                    differentstocksWithQuantity.clear();
                    differentstocksWithQuantityNumbers.clear();
                    k = k + linearCombination[i];
                    i++;
                }
                if (NoTrade)
                {
                    std::cout << "No Trade" << std::endl;
                }
            }
        }

        totalLine++;
    }
}