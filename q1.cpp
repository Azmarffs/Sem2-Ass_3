/*
Name: Azmar Kashif
Section: B
Roll no: 22i-2716
*/
#include<iostream>
#include<string>
using namespace std;
class Block{
    string shape; //arr to store the type of shapes for the block
    string color;
    public:
    //parameterized constructor but we also give it default val in the parameters to make it work like default aswell
    Block(string s = "", string c = ""){ 
        shape = s;
        color = c;
    }
    ostream & display(ostream& out) const{
        if(color != ""){ //here we check if color is not empty then we display its shape aswell as color
            out << "( " << shape << ", " << color << ")";
        }else{ //else we display only its shape
            out << ", " << shape << ")";
        }
        return out;
    }
};
/*
overloading insertion operator to display block features
*/
ostream& operator<<(ostream& out, Block& b){ 
    return b.display(out);
}
//making a child clas inherited by parent class
class Build : public Block{
    private:
    // data members
    Block*** content;
    int height = 1;
    int depth = 1;
    int width = 1;

public:
//parametrized constructor for making 3D dynamic array for block
    Build(Block& block) {
        content = new Block**[height];
        for (int i = 0; i < height; i++) {
            content[i] = new Block*[depth];
            for (int j = 0; j < depth; j++) {
                content[i][j] = new Block[width];
                for (int k = 0; k < width; k++) {
                    content[i][j][k] = block;
                }
            }
        }
    }
    /*
    To make the layers of each block
    */
    ostream& display(ostream& out) const {
        for (int i = 0; i < height; i++) {
            out << "Layer: " << i+1 << ":" << endl;
            for (int j = 0; j < depth; j++) {
                for (int k = 0; k < width; k++) {
                    out << content[i][j][k] << " ";
                }
                out << endl;
            }
        }
        return out;
    }
    //to display the layers 
    friend ostream& operator<<(ostream& out, const Build& build) {
        return build.display(out);
    }
    /*
    Overloading ^= operator
    */
    Build operator^=(Build& b){ 

        int totalHeight = height + b.height; //we first measure total height
        /*
        Here we make a new dyanimic 3D array for height as we
        are increasing height of block in this function
        */
        Block*** contentAfterNewH = new Block**[totalHeight]; 
        /*
        running each loop till total height and 
        storing h w d in contentAfterNewH pointer
        */
        for(int i =0;i<totalHeight;i++){
            contentAfterNewH = new Block**[height];
            for(int j=0;j<totalHeight;j++){
                contentAfterNewH = new Block**[depth];
                for(int k =0;k<totalHeight;k++){
                    /*
                    here we check if height is greater
                    if its greater than we give the value of content
                    to contentAfterNewH without making any changes
                    */
                    if(i < height){
                        contentAfterNewH[i][j][k] = content[i][j][k];
                    }else{ //else we minus the height from the org height
                        contentAfterNewH[i][j][k] = b.content[i - height][j][k];
                    }
                }
            }
        }
        /*
        deleting the memory
        */
        for(int i=0;i<height;i++){
            for(int j=0;j<depth;){
                delete[] contentAfterNewH[i][j];                
            }
            delete[] contentAfterNewH[i];
        }
        delete[] contentAfterNewH;
        content = contentAfterNewH;
        height += b.height;
        return* this;
    }
    /*
    overloading ^ operator 
    */
    Build operator^(const Block& a) {
        Build temp(*this); //making a temp obj and  passing *this to its parametrized constructor
        temp = temp ^ a; //this is used to place the whole block layer over another
        return temp;
    }
    /*
    overloading -= operator
    */
    Build operator-=(const Build& b){
        /*
        here we do the same thign make new 3d dynamic array and storing h w d in it
        */
        Block*** newBlockForHeight = new Block**[height];
        //checking if curr block widht is greater than previous block
        if(b.width > width){
            return* this;
        }
        //but here we inc height after every iteration because we adding block in its height
        newBlockForHeight = new Block**[height+1];
        for(int i=0;i<height;i++){
            newBlockForHeight = new Block**[depth];
            for(int j=0;j<depth;j++){
                newBlockForHeight = new Block**[width]; //doing heigth++ because we're adding blocks along its height
                for(int k=0;k<width;k++){
                    newBlockForHeight[i][j][k] = content[i][j][k];
                }
                /*
                here we only make changes in the height and depth but not in width
                */
                newBlockForHeight[i][j][width] = b;
            }
        }
        //deleting memory
        for(int i=0;i<height;i++){
            for(int j=0;j<depth;j++){
                delete[] content[i][j];
            }
            delete[] content[i];
        }
        delete[] content;
        content = newBlockForHeight;
        height = height + 1;
    }
    //overloading - operator
    friend Build operator-(const Build& a, const Build& b){
        Block temp = a; //making a temp obj and inializiing it with a obj
        temp = temp - b; //this will add blocks behind existing block
        return temp;
    }
    /*
    overloading += operator
    */
    Build operator+=(const Build& b){
        Block*** newBlockForWidth = new Block**[height];
        //we check if the height of block to be added is greater than the height of previus blocks
        if(b.height > height){
            return* this; //then we return it without any changes
        }
        /*
        running loop for each h w d of the block dynamically
        */
        newBlockForWidth = new Block**[height];
        for(int i=0;i<height;i++){
            newBlockForWidth = new Block**[depth];
            for(int j=0;j<depth;j++){
                newBlockForWidth = new Block**[width+1]; //doing width+1 because we're adding blocks along its width
                for(int k=0;k<width;k++){
                    newBlockForWidth[i][j][k] = content[i][j][k];
                }
                newBlockForWidth[i][j][width] = Block(b);
            }
        }
        //deleting the memory
        for(int i=0;i<height;i++){
            for(int j=0;j<depth;j++){
                delete[] content[i][j];
            }
            delete[] content[i];
        }
        delete[] content;
        content = newBlockForWidth;
        width = width + 1;
    }
    //overloading + operator
    friend Build operator+(const Build& a, const Build& b){
        Block temp = a;
        temp = temp + b; //here we are adding blocks to the right of existring blocks
        return temp;
    }
  
    friend Build operator*(unsigned int n, Build const& a){
        Build c(a);
        for(int i=0;i<n;i++){ //repeating it till n-1 times 
        c += a;
        }
        return c;
    }
    friend Build operator/(unsigned int n, Build const& a){
        Build c(a);
        for(int i=0;i<n;i++){ //repeating it till n-1 times
            c = c ^ a;
        }
        return c;
    }
    friend Build operator%(unsigned int n, Build const& a){
        Build c(a);
        for(int i=0;i<n;i++){  //repeating it till n-1 times
            c -= a;
        }
        return c;
    }
};


int main() {
    Block b1("Simple", "red");
    Block b2("ObliqueL", "blue");
    Block b3("ObliqueR", "green");


    Build tower1(b1);
    cout << "Making towers" << endl;
    cout << tower1 << endl; 
    Build tower2(b2);
    cout << tower2 << endl; 
    Build tower3(b3);
    cout << tower3 << endl; //

    Build myBuild(b1);
    myBuild.display(cout);

    
    cout << "Adding different layers" << endl;
    tower1 ^= tower2; 
    tower1 ^= tower3; 
    cout << tower1 << endl; 

    // tower1 -= tower2; 
    cout << tower1 << endl; 
}

