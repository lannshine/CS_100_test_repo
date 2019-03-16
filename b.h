#ifndef B_H
#define B_H

class B {
    public:
        B* left = 0;
        B* right = 0;
        B() {}
        void MakeRoots(B* l, B* r) {
            this->left = l;
            this->right = r;
        }
        virtual bool evaluate(int in, int out) = 0;
};

#endif