if g++ main.cpp -o main -lGL -lglfw; then
    mv main Linux
    ./Linux/main
else
    echo "Error"
fi