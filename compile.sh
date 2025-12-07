clang++ -std=c++20 -Wall -o SocialNetwork main.cpp

if [ $? -eq 0 ]; then
    echo "Compilation Successful"
    echo "Run with ./SocialNetwork"
else
    echo "Compilation failed"
fi