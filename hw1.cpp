/** Name: Kendrick Chu
 Date: 4/4/16
 @File: hw1.cpp
 @Brief: The program uses polymorphism to create ThingA and ThingB objects derived from a Thing base class, and these objects are stored using a Board class object.  Operator overloading is used to print out the objects within the Board class, to check if there is an object within the Board object at a certain position, and to compare the objects in the Board object to see if there are duplicates.
 */

#include <iostream>
#include <string>
#include <vector>

class Board; //forward declaration

/** @class Thing
 @Brief Stores the Thing class
 
 This is the Thing base class consisting of a position.
 */
class Thing{
public:
    /** Constructor the makes a specified position into the object's position
     @param int pos is the position of the Thing object
     */
    Thing(int pos) : position(pos) { };
    /** Returns the position of the object
     @returns the position of the object
     */
    virtual int get_position() const {return position;};
    /** Virtual print function used to print out all Thing objects and objects derived from this class
     @param std::outstream& out is the outstream variable used to print
     */
    virtual void print(std::ostream& out) const { };
    
protected:
    int position;
};

/** @class ThingA
 @Brief Stores the ThingA class
 
 This is the ThingA class derived from the Thing base class, which consists of a position, string property, and board.
 
 */
class ThingA : public Thing {
public:
    /** Constructor that initializes the position, property, and board to specified values
     @param int pos is the position of the ThingA object
     @param std::string prop is the string property of the ThingA object
     @param const Board& b is the constant reference to the board object of ThingA
     */
    ThingA(int pos, std::string prop, const Board& b) : Thing(pos), property(prop), board(b) { };
    /** Prints out the position and property of the object
     @param std::ostream& out is the outstream variable used to print
     */
    void print(std::ostream& out) const {out << "A:" << get_position() << ":" << property;};
    
private:
    std::string property;
    const Board& board;
};

/** @class ThingB
 @Brief Stores the ThingB class
 
 This is the ThingB class derived from the Thing base class, which consists of a position, double property, and board.
 */
class ThingB : public Thing {
public:
    /** Constructor that initializes the position, property, and board to specified values
     @param int pos is the position of the ThingB object
     @param double prop is the double property of the ThingB object
     @param const Board& b is the constant reference to the board object of ThingB
     */
    ThingB(int pos, double prop, const Board& b) : Thing(pos), property(prop), board(b) { };
    /**Makes the object have a new position
     @
     */
    bool propose_new_position(int a);
    /** Prints out the position and property of the object
     @param std::ostream& out is the outstream variable used to print
     */
    void print(std::ostream& out) const {out << "B:" << get_position() << ":" << property;};
    
private:
    double property;
    const Board& board;
};

/** @class Board
 @Brief Stores the Board class
 
 This is the Board class which stores Thing objects and all derived objects of the thing class into a vector.
 */
class Board{
public:
    /** Checks whether or not there is a  thing in the Thing* vector at a certain position
     @param int pos is the specified position
     @returns true if there is an element at the specified position or flase if there is not an element at the specified position
     */
    bool ParticleInPosition(int pos) const {
        //Checks each element in the vector if there is an element at at certain specified position
        for(size_t i = 0; i < things.size(); ++i)
            //If there is an element at the specified position, return true or 1
            if(things[i]->get_position() == pos)
                return true;
        //Else return false or 0
        return false;
    };
    
    /** Adds a ThingA element to the Thing* vector
     @param int pos is the position used for the new ThingA
     @param std::string prop is the string property used for the new ThingA
     */
    void AddAParticle(int pos, std::string prop) {
        ThingA* thing = new ThingA(pos, prop, *this);
        things.push_back(thing);
    };
    
    /** Adds a ThingB element ot the Thing* vector
     @param int pos is the position used for the new ThingA
     @param double prop is the double property used for the new ThingB
     */
    bool AddBParticle(int pos, double prop) {
        
        //if no particle is at position pos, then add, otherwise don't add.
        if(!ParticleInPosition(pos)) {
            ThingB* thing = new ThingB(pos, prop, *this);
            things.push_back(thing);
            return true;
        }
        return false;
    };
    
    /** Prints out the elements in the things vector
     @param std::ostream& out is the outstream variable being used to output the elements in the things vector
     */
    void print(std::ostream& out) const {
        //Print out each element in the things vector, separated by an endl
        for(size_t i=0, n=things.size(); i < n; ++i){
            things[i]->print(out);
            std::cout << std::endl;
        }
    };
    
    /** Checks whether or not there is an element in the specified position using the ParticleInPosition function
     @returns the result of the ParticleInPosition function
     */
    bool operator[](int pos){
        return ParticleInPosition(pos);
    };
    
    /** Checks whether or not the particles of the board object are different
     @returns true or 1 if there are the same particles on the board
     @returns false or 0 if all the particles on the board are different
     */
    bool operator()() {
        //For every element in the things variable, check each element with all elements after it
        for(size_t i = 0, n = things.size(); i < n; ++i)
            //Used to compare the element in the first for loop
            for(size_t k = 1, n = things.size(); k < n; ++k) {
                //If there are multiple of the same particles on the board, return true
                if(things[i] == things[k])
                    return true;
            }
        //Else return false
        return false;
    };
    
private:
    std::vector<Thing*> things;
};

/** Uses the print function to print out the objects in the vector contained in the Board object using the << operator
 @param std::ostream& out is the outstream variable to that is used in the print function
 @param const Board& b is a constant reference to the Board variable, which is the object that the operator << is acting on
 @returns the outstream variable
 */
std::ostream& operator <<(std::ostream& out, const Board& b) {
    b.print(out);
    return out;
};

int main() {
    
    Board test;
    //Testing operator << on empty board, should return nothing
    std::cout << test << std::endl;
    
    //Testing operator [] on empty board, should return 0
    std::cout << test[0] << std::endl;
    
    //Add particles to the board
    test.AddAParticle(0, "red");
    test.AddBParticle(9, 2.71828);
    test.AddAParticle(7, "yellow");
    
    //Test operator << on board with particles, should print out particles added above
    std::cout << test;
    
    //Test oeprator [] on board with particles, both particles in existence and not in existence, should return 1 for existing particles and return 0 for non-existing particles
    std::cout << test[0] << std::endl;
    std::cout << test[3] << std::endl;
    
    //Test operator () on board with no particles, should return 0
    Board test1;
    std::cout << test1() << std::endl;
    
    //Add two of the same particles to the board
    test1.AddAParticle(2, "blue");
    test1.AddAParticle(2, "blue");
    
    //Test operator () on board with same particles, should return 1
    std::cout << test1() << std::endl;
    
    //Add two different particles to a different board
    Board test2;
    test2.AddAParticle(3, "black");
    test2.AddBParticle(3, 6.8795);
    
    //Test operator () on board with different particles, should return 0
    std::cout << test2() << std::endl;
    
    //Test operator () on board with random particles
    Board test3;
    test3.AddAParticle(3, "black");
    test3.AddAParticle(0, "red");
    test3.AddBParticle(2, 5.4623);
    test3.AddAParticle(3, "black");
    
    //Test operator () should return 1
    std::cout << test3() << std::endl;
    
    
    return 0;
}