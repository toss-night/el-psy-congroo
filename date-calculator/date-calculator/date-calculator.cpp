#include <iostream>
#include <chrono>

std::chrono::system_clock::time_point makeTimePoint(short dy, short mh, short yr, short h, short m, short s) {
    auto userDate = std::chrono::year_month_day(std::chrono::year(yr), std::chrono::month(mh), std::chrono::day(dy));
    auto tempTimeP = std::chrono::sys_days(userDate);
    auto timeP = tempTimeP + std::chrono::hours(h) + std::chrono::minutes(m) + std::chrono::seconds(s);

    return timeP;
}
std::chrono::system_clock::time_point makeTimePoint() {
    short s, m, h, dy, mh, yr;
    std::cout << "choise date.\nenter day: ";
    std::cin >> dy;
    std::cout << "enter month: ";
    std::cin >> mh;
    std::cout << "enter year: ";
    std::cin >> yr;
    std::cout << "enter hours: ";
    std::cin >> h;
    std::cout << "enter minutes: ";
    std::cin >> m;
    std::cout << "enter seconds: ";
    std::cin >> s;

    auto userDate = std::chrono::year_month_day(std::chrono::year(yr), std::chrono::month(mh), std::chrono::day(dy));
    auto tempTimeP = std::chrono::sys_days(userDate);
    auto timeP = tempTimeP + std::chrono::hours(h) + std::chrono::minutes(m) + std::chrono::seconds(s);

    return timeP;
}

std::chrono::system_clock::duration findDifference(std::chrono::system_clock::time_point firstTp, std::chrono::system_clock::time_point secondTp) {
    if (firstTp < secondTp) {
        auto timeD = secondTp - firstTp;
        return timeD;
    }
    else if (firstTp > secondTp) {
        auto timeD = firstTp - secondTp;
        return timeD;
    }
    else {
        auto timeD = std::chrono::seconds::zero();
        return timeD;
    }  
}
std::chrono::system_clock::duration findTimeBeforeOrAfter(std::chrono::system_clock::time_point timePoint) {
    auto tempTimeN = std::chrono::system_clock::now();
    auto timeN = std::chrono::time_point_cast<std::chrono::seconds>(tempTimeN);

    if (timePoint > timeN) {
        auto timeD = timePoint - timeN;
        return timeD;
    }
    else if (timePoint < timeN) {
        auto timeD = timeN - timePoint;
        return timeD;
    }
    else {
        auto timeD = std::chrono::seconds::zero();
        return timeD;
    }
}

void printDifference(std::chrono::system_clock::duration& diff) {
    auto diffDays = std::chrono::duration_cast<std::chrono::days>(diff);
    auto diffHours = std::chrono::duration_cast<std::chrono::hours>(diff - diffDays);
    auto diffMinutes = std::chrono::duration_cast<std::chrono::minutes>(diff - diffDays - diffHours);
    auto diffSeconds = std::chrono::duration_cast<std::chrono::seconds>(diff - diffDays - diffHours - diffMinutes);
    std::cout << "difference: " << diffDays << ", " << diffHours << ", " << diffMinutes << ", " << diffSeconds << ".\n";
}


int main() {
    short choise; 
    std::cout << "find time before or after(1) or find time between(2): ";
    std::cin >> choise;

    if (choise == 1) {
        auto timeP = makeTimePoint();
        auto diff = findTimeBeforeOrAfter(timeP);
        printDifference(diff);
    }
    else if (choise == 2) {
        auto firstTp = makeTimePoint();
        auto secondTp = makeTimePoint(); 
        auto diff = findDifference(firstTp, secondTp);
        printDifference(diff);     
    }    
    return 0;
}