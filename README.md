# AccessPoint-problem
A problem that represents the final exam in the oop class. 

To improve security in the university faculty building during this challenging period, you have decided to implement an access control system for card-based entry to the building and offices. The system works with RFID cards, and each door in the faculty has a card reader that synchronizes with a central database and controls an electromagnetic locking system. The first development phase involves implementing a simulator that will be later used as an activity log analyzer.

In the application, you are required to implement the following classes, methods, and operators:

Class AccessPoint:

Models a door.
Encapsulates the following data:
mUnlocked of type bool, representing the door's state (unlocked or locked).
Implements a parameterless constructor that initializes mUnlocked to false.
Implements a getter method for the mUnlocked field called isUnlocked.
Implements a method void toggle() that changes the door's state (from locked to unlocked and vice versa).
Class AccessDeniedException:

Publicly extends std::exception with a default constructor.
Class User:

Models a card user.
Encapsulates the following data:
mUserId of type std::string, representing the user's name.
mCards of type std::set<uint64_t>, representing the user's cards.
mAccessPoints of type std::vector<AccessPoint*>, representing the doors the user has access to.
mActivity of type uint32_t, representing the number of door locking/unlocking operations performed by the user.
Implements a constructor that takes a user ID (as a const reference to std::string) and initializes mUserId with that ID, mCards, and mAccessPoints with empty collections.
Implements a method void toggleDoor(AccessPoint*) that checks if the user has access to the given door. If the user has access, the method changes the door's state (from locked to unlocked and vice versa). If the user does not have access, the method throws an AccessDeniedException.
Implements a method void addAccessPoint(AccessPoint*) that adds a door to the user's list of accessible doors if it does not already exist. If it exists, the method does nothing.
Implements a method void addCard(uint64_t) that adds a card to the user if it does not already exist. If it exists, the method does nothing. The argument represents the card ID.
Implements a method bool hasCard(uint64_t) that returns true if the card belongs to the user. The argument represents the card ID.
Implements a method uint32_t countCards() that returns the number of cards the user has.
Implements a method uint32_t getActivity() that returns the number of door locking/unlocking operations performed by the user.
Class AdminUser:

Extends the User class with the only modification being the override of the toggleDoor method, which will never throw an exception because an AdminUser has access to all doors by default.
Class Database:

Contains all application data.
Encapsulates the following data:
mUsers of type std::map<std::string, User*>, where the key is the user ID.
mAccessPoints of type std::unordered_map<uint64_t, AccessPoint>, where the key is the door ID.
Implements methods to add users, doors, cards to users, and access points to users.
Implements a method to parse events (door locking/unlocking attempts) and perform the corresponding actions based on the user's access permissions.
Four methods corresponding to the given requirements:

countUnlockedDoors()
countActivity()
findUsersWithNoCards()
countCards()
Requirements:

Display the number of doors that remained unlocked at the end (after all events were processed) - a single number.
Display the total number of door locking/unlocking operations for all doors - a single number.
Display the names of users who have no active cards, ordered alphabetically. If no user has no active card, display a newline (\n).
Display the total number of enrolled cards in the system - a single number.
Display the number of attempted unauthorized accesses (unknown card code or attempting to lock/unlock a door where the user does not have access) - a single number.
Input:

The first line contains three unsigned integer values (n, m, and k) representing the number of access points, users, and events to interpret.
The next n lines contain 64-bit unsigned integers representing the IDs of access points (doors).
The following m lines contain the definition of a user in the following format, where the user type is represented by the character U for a regular user or A for an admin:
<user_id> <user_type> <c=num_cards> <card_id_1> ... <card_id_c> <u=num_doors> <door_id_1> ... <door_id_u>
The next k lines contain events in the format <access_point_id> <card_id>, representing an attempt to lock/unlock the door with the specified access_point_id using the card with the given card_id.
The last line contains one of the numbers 1-5, representing the requirement to be solved.
Output:

Output the results based on the specified requirements.
Note: It is permitted to add additional methods or fields to make the problem easier to solve.
