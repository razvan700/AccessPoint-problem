#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class AccessPoint
{
private:
    bool mUnlocked;
public:
    AccessPoint()
    {
        mUnlocked = false;
    }
    bool isUnlocked()
    {
        return mUnlocked;
    }
    void toggle()
    {
        mUnlocked = !mUnlocked;
    }
};

class AccessDeniedException : public exception{};

class User
{
private:
    string mUserId;
    set<uint64_t> mCards;
protected:
    vector<AccessPoint *> mAccessPoints;
    uint32_t mActivity;
public:
    User(string userID)
    {
        mUserId = userID;
        mCards = set<uint64_t>();
        mAccessPoints = vector<AccessPoint *>();
    }

    virtual void toggleDoor(AccessPoint *Acces)
    {
        if (find(mAccessPoints.begin(), mAccessPoints.end(), Acces) != mAccessPoints.end()) {
            Acces->toggle();
            mActivity++;
        }

        else throw AccessDeniedException();
    }

    void addAccessPoint(AccessPoint *Acces)
    {
        if (find(mAccessPoints.begin(), mAccessPoints.end(), Acces) == mAccessPoints.end())
            mAccessPoints.emplace_back(Acces);
    }
    void addCard(uint64_t card)
    {
        if (!hasCard(card))
            mCards.insert(card);
    }
    bool hasCard(uint64_t card)
    {
        bool found = false;
        for(uint64_t c : mCards)
            if(card == c) {
                found = true;
                break;
            }
        return found;
    }
    uint32_t countCards()
    {
        return mCards.size();
    }
    uint32_t getActivity()
    {
        return mActivity;
    }
};

class AdminUser : public User
{
public:
    explicit AdminUser(string ID) : User(ID) {}
    void toggleDoor(AccessPoint *Acces) override
    {
        if (find(mAccessPoints.begin(), mAccessPoints.end(), Acces) != mAccessPoints.end())
        {
            Acces->toggle();
            mActivity++;
        }
    }
};

class Database
{
private:
    map<string, User*> mUsers;
    unordered_map<uint64_t, AccessPoint> mAccessPoints;
public:
    void addUser(const string& userID, char userType)
    {
        switch (userType) {
            case 'A':
                mUsers.insert(make_pair(userID, new AdminUser(userID)));
                break;
            case 'U':
                mUsers.insert(make_pair(userID, new User(userID)));
                break;
            default: ;
        }
    }
    void addAccessPoint(uint64_t apID)
    {
        mAccessPoints.insert(make_pair(apID, AccessPoint()));
    }
    void addCardToUser(const string& userID, uint64_t card)
    {
        mUsers.at(userID)->addCard(card);
    }
    void addAccessPointToUser(const string& userID, uint64_t apID)
    {
        mUsers.at(userID)->addAccessPoint(&mAccessPoints.at(apID));
    }
    void parseEvent(uint64_t card, uint64_t ap)
    {
        for(auto user : mUsers)
            if(user.second->hasCard(card))
            {
                user.second->toggleDoor(&mAccessPoints.at(ap));
                return;
            }
        throw AccessDeniedException();
    }
    uint32_t  countUnlockedDoors()
    {
        uint32_t unlockedDoors = 0;
        for(auto door : mAccessPoints)
            if(door.second.isUnlocked())
                unlockedDoors++;
        return unlockedDoors;
    }
    uint32_t countActivity()
    {
        uint32_t activityCount = 0;
        for(auto user : mUsers)
            activityCount += user.second->getActivity();
        return activityCount;
    }
    vector<string> findUsersWithNoCards()
    {
        vector<string> users;
        for(auto user : mUsers)
            if(!user.second->countCards())
                users.emplace_back(user.first);
        return users;
    }
    uint32_t countCards()
    {
        uint32_t cardsCount = 0;
        for(auto user : mUsers)
            cardsCount += user.second->countCards();
        return cardsCount;
    }
};

int main()
{
    uint32_t n, m, k;
    std::cin >> n >> m >> k;
    Database database;
    while(n--)
    {
        uint64_t accessPointId;
        std::cin >> accessPointId;
        database.addAccessPoint(accessPointId);
    }
    while(m--)
    {
        std::string userId;
        char type;
        std::cin >> userId >> type;
        database.addUser(userId, type);
        uint32_t c;
        std::cin >> c;
        while(c--)
        {
            uint64_t cardId;
            std::cin >> cardId;
            database.addCardToUser(userId, cardId);
        }
        uint32_t u;
        std::cin >> u;
        while(u--)
        {
            uint64_t accessPointId;
            std::cin >> accessPointId;
            database.addAccessPointToUser(userId, accessPointId);
        }
    }
    uint32_t errors = 0;

    while(k--)
    {
        uint64_t accessPointId, cardId;
        std::cin >> accessPointId >> cardId;
        try {
            database.parseEvent(cardId, accessPointId);
        }catch(AccessDeniedException & ex) {
            errors++;
        }

    }
    uint32_t subject;
    std::cin >> subject;
    switch(subject)
    {
        case 1:
        {
            std::cout << database.countUnlockedDoors();
            break;
        }
        case 2:
        {
            std::cout << database.countActivity();
            break;
        }
        case 3:
        {
            auto users = database.findUsersWithNoCards();
            if(users.empty())
                std::cout << "\n";
            else{
                for(const auto & user : users) std::cout << user << " ";
                break;
            }
        }
        case 4:
        {
            std::cout << database.countCards();
            break;
        }
        case 5:
        {
            std::cout << errors;
            break;
        }
    }
    return 0;
}