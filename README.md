# SocialNet-Simulator
This repository contains the long assignment cum project in which I have implemented a Social Network from scratch.

In this assignment I have built build SocialNet, a command-line simulator for a social network’s backend services. I have implemented core functionalities for managing users, friendships, and content. The core data structures I have used for this implemenetation are AVL Trees and graphs

***
### Compilation procedure
I named this Social System as `SocialNetwork`. To begin the program the following command must be entered in the terminal.
```bash
chmod +x compile.sh
```
After running this command once, the file is permanently marked as executable, and you can run it anytime using:
```bash
./compile.sh
```
**Note:** I have added the command clang++ to create the executable as per my system (MacOS), it could be changed to g++ if on Windows.
On succesful execution the following prompt appears:
```bash
Compilation Succesful
Run with ./SocialNetwork
```
else if the compilation fails, this prompt is displayed on the terminal:
```bash
Compilation failed
```
On successful compilation type `./SocialNetwork` to enter into the program. The start of program displays:
```bash
Welcome to Social Network
Type EXIT to quit the program
```

## Social Network Operations
Each line begins with 
```bash
>> 
```
The following are the core operations supported by the program:
* ### Adding a user
    
    ```bash
    ADD_USER <username>
    ```
    **Assumptions**: 
    * The username is not case sensitive, xyz is equivalent to XYZ and will be displayed as XYZ over the social network.
    * The username must be unique for each user.
    * The username should not have any space.
    * username should have atleast one of the characters other than space.
    
    **NOTE:** If the username contains space then the first word would be taken as the username.
* ### Adding friend
    ```bash
    ADD_FRIEND <username1> <username2>
    ```
    Error handling is implemented if the users have not been added to the network before(this means that any such username does not exist in the user network).
* ### Listing the friends of a user
    ```bash
    LIST_FRIENDS <username>
    ```
    The username should be non empty string and must have been added to the network beforehand.

    Error handling is implemented if the command `ADD_USER <username>` has not been ran for this user before(this means that any such username does not exist in the user network).
* ### Friends suggestion to a user
    ```bash
    SUGGEST_FRIENDS <username> <N>
    ```
    The suggestions are ranked on the basis of :
    * Ranking: Recommendations are ranked by the number of mutual friends (descending). Ties are broken by ascending alphabetical order of usernames.
    * Edge Cases: If N is 0, output nothing. If fewer than N candidates exist, list all available.
    Error handling is implemented if the command `ADD_USER <username>` has not been ran for this user before(this means that any such username does not exist in the social network).
* ### Degrees of seperation between two users
    ```bash
    DEGREES_OF_SEPARATION <username1> <username2>
    ```

    If the friends are not connected in the social network then their degree is displayed as -1.

    Error handling is implemented if the commands `ADD_USER <username>` have not been ran for this file before(this means that any such usernames does not exist in the social network).

## User Content Operations
* ### Adding a post
    ```bash
    ADD_POST <username> "<post content>"
    ```
    For the first command:

    The username should be there is the social network (meaning that it should have been created by some previously by the `ADD_USER <username>` command).The error handling is implemented.
    **Key Assumption :*** The time resolution for adding posts is 1 second. No two posts can be entered within an interval of less than 1 sec.
    The timestamp of the post is stored along with the \<post content>.
    
* ### Output Latest Posts
    ```bash
    OUTPUT_POSTS <username> <N>
    ```
    Outputs the most recent N posts of the user, in reverse chronological order.
    If N=-1 then all th posts of the user are displayed.

Anything else entered that does not have the above mentioned commands as its prefix is handled by displaying unknown command.


