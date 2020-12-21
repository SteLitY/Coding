//This is a program I've written for my Algorithms course at Hunter College

//The function weight returns the sum of all elements in the rectangle defined by the points (x1,y1) and (x2,y2)
//The weight function is O(1). Precomputation of the weight is O(N)

//PathCost computes the cheapest path from the top left corner of the field to the bottom right corner.
//The only possibles moves are right and down.


#ifndef FIELD
#define FIELD

#include <iostream>
#include <vector>
#include <stdexcept>

class Field
{
    public:

    Field(const std::vector< std::vector<int> > & constructorVector)
    {
        inputVec.resize(constructorVector.size());

        for(int i = 0; i < constructorVector.size(); i++)
        {
            inputVec[i].resize(constructorVector[i].size());
            for (int j = 0; j < constructorVector[i].size(); j++)
            {
                inputVec[i][j] = constructorVector[i][j];
            }

        }

        preComputeWeightVector();
        precalculatePathCost();
    }

    Field(std::vector<std::vector<int>> && constructorVector)
    {
        inputVec.resize(constructorVector.size());

        for(int i = 0; i < constructorVector.size(); i++)
        {
            inputVec[i].resize(constructorVector[i].size());
            for (int j = 0; j < constructorVector[i].size(); j++)
            {
                inputVec[i][j] = constructorVector[i][j];
            }

        }

        preComputeWeightVector();
        precalculatePathCost();
    }

    int Weight(int x1, int y1, int x2, int y2)
    {
        //throws exception if input contains a negative number
        if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
        {
            throw std::out_of_range("Please enter a positive number for Weight.\n");
        }
        
        //throws exception if human tries to go to a coordinate that is not in the vector
        if(inputVec.empty() || x1 >= inputVec.size() || x2 >= inputVec.size() ||y1 >= inputVec.size() ||  y2 >= inputVec.size() )
        {
            throw std::out_of_range("Please enter a position that is within the vector.\n");
        }

        //find smallest x and largest x to calculate the rectangle
        //(1,1),(4,4) gives the exact same rectangle as (1,4),(4,1). You can reverse the order of (x1,y1) and (x2,y2) and still get the same rectangle. ex: (1,4),(4,1) == (4,1),(1,4)
        //The smallest x,y and the largest x,y will give us the same rectangle every time.
        int largestX = x1;
        int largestY = y1;
        int smallestX = x2;
        int smallestY = y2;
    
        if (x2 > x1)
        {
            //by default x1 > x2
            largestX = x2;
            smallestX = x1; 
        } 
        if (y2 > y1)
        {
            //by default y1 > y2
            largestY = y2;
            smallestY = y1; 
        } 

        //now we know weight[largestY,largestX] gives us the sum of everything starting from weight[0][0]
        //if weight[smallestY -1][largestX] exists, it gives us the rectangle that we have to subtract
        //if weight[largestY][smallestX -1] exists, it gives us the other rectangle that we have to subtract
        //if weight[smallestY -1][smallestX -1] exists, we must add this value back.

        int totalWeight = weight[largestY][largestX];

        //subtract the rectangle on top
        if (smallestY > 0) //That means smallestY-1 exists in the 2d vector
        {   
            //subtract the rectangle that we don't need
            totalWeight = totalWeight - weight[smallestY - 1][largestX];
        }

        //subtract the rectangle to the left
        if (smallestX > 0) //That means smallestX-1 exists in the 2d vector
        {
            totalWeight = totalWeight - weight[largestY][smallestX - 1];
        }

        //add the rectangle  that we subtracted twice
        if ( (smallestX > 0) && (smallestY > 0) )
        {
            totalWeight = totalWeight + weight[smallestY-1][smallestX-1];
        }

        return totalWeight;
    }

    int PathCost()
    {
        return pathCost;
    }

    void displayVector(const std::vector< std::vector <int> > &vec)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            for (int j = 0; j < vec[i].size(); j++)
            {
                std::cout << vec[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    void displayVector()
    {
        for (int i = 0; i < inputVec.size(); i++)
        {
            for (int j = 0; j < inputVec[i].size(); j++)
            {
                std::cout << inputVec[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
        void displaySum()
    {
        for (int i = 0; i < weight.size(); i++)
        {
            for (int j = 0; j < weight[i].size(); j++)
            {
                std::cout << weight[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

/****************************************************************************/

    private:
    std::vector<std::vector <int> > inputVec;
    std::vector<std::vector<int>> weight;
    int pathCost;

    void preComputeWeightVector()
    {    
        weight.resize(inputVec.size());

        for (int i = 0; i < inputVec.size(); i++)
        {
            weight[i].resize(inputVec[i].size());
        }

        /**************************/
        //Breaking apart loop in steps to avoid if statements. 
        weight[0][0] = inputVec[0][0];

        //do all the left side wall first
        //skip [0][0] since it was already done.
        int counter = 1;
        while(counter != inputVec.size())
        {   
            weight[counter][0] = weight[counter-1][0] + inputVec[counter][0];

            counter++;
        }

        //do the top wall. vec[0][j]
        for(int i = 1; i < inputVec[0].size(); i++)
        {
            weight[0][i] = weight[0][i-1] + inputVec[0][i];

        }
        
        //now the rest
        for (int i = 1; i < inputVec.size(); i++)
        {
            int total = inputVec[i][0];
            for (int j = 1; j < inputVec[i].size(); j++)
            {
                total = total + inputVec[i][j];
                weight[i][j] = weight[i-1][j] + total; 
            }
        }

    } //end of preComputeWeightVector

    void precalculatePathCost()
    {
        std::vector< std::vector<int>> path;
        path.resize(inputVec.size());

        for (int i = 0; i < inputVec.size(); i++)
        {
            path[i].resize(inputVec[i].size());
        }

        //prefill top row and left wall because you can only move down and right. 
        path[0][0] = inputVec[0][0];

        //prefill top
        int smallestCost = path[0][0];
        for (int i = 1; i < path[0].size(); i++)
        {
            smallestCost = smallestCost + inputVec[0][i];
            path[0][i] = smallestCost;
        }

        //prefill left wall
        for (int i = 1; i < path.size(); i++)
        {
            path[i][0] = path[i-1][0] + inputVec[i][0];
        }

        //do the rest from left to right then down to next row
        for (int i = 1; i < path.size(); i++)
        {
            for (int j = 1; j < path[i].size(); j++)
            {
                //since we filled the top and left wall, we can just run this loop with fewer if statements.
                int top = path[i-1][j];
                int left = path[i][j-1];
                if (top > left)
                {
                    path[i][j] = inputVec[i][j] + left;
                }
                else
                {
                    path[i][j] = inputVec[i][j] + top;
                }
                
            }
        }

        //Assuming that all rows are the same size
        pathCost = path[path.size()-1][path[0].size()-1];
        

        // std::cout << "Path\n";
        // displayVector(path);
        // std::cout << "\n";
    }

};

#endif

int main()
{
    std::vector< std::vector<int>> vec { {1,2,3,4,5,96,7}, {1,2,3,4,5,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7} };

    Field A({ {1,2,3,4,5,96,7}, {1,2,3,4,5,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7} });

    A.displayVector();
    std::cout << "\nSum:\n";
    A.displaySum();
    std::cout << "\nWeight: " << A.Weight(2,1,2,1);

    // std::cout << "\nPath: " << A.PathCost() << "\n";
    // Field B(std::vector< std::vector<int>> { {1,2,3,4,5,96,7}, {1,2,3,4,5,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7} });
    // B.displayVector();
    // std::cout << "\nSum:\n";
    // B.displaySum();
    // std::cout << "\nWeight: " << B.Weight(0,0,2,1);
    // std::cout << "\nPath: " << B.PathCost() << "\n";

    // Field f{ std::vector< std::vector<int>> (6,{1,2,3,4,5,6,7})};
    // f.displayVector();
    // std::cout << "\nSum:\n";
    // f.displaySum();
    // std::cout << "\nWeight: " << f.Weight(0,0,2,1);
    //  std::cout << "\nPath: " << f.PathCost() << "\n";
}

// int main()
// {
    // std::vector< std::vector<int>> { {1,2,3,4,5,96,7}, {1,2,3,4,5,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7} };

//     std::vector< std::vector<int>> a { {1,2,3,4,5,96,7}, {1,2,3,4,5,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7}, {1,2,3,4,95,6,7} }
//     Field B(a);
//     B.displayVector();
//     std::cout << "\nSum:\n";
//     B.displaySum();
//     std::cout << "\nWeight: " << B.Weight(0,0,2,1);
//     std::cout << "\nPath: " << B.PathCost() << "\n";
// }