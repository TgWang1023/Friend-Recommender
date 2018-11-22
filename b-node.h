class B_Node {
    public: 
        B_Node();
        B_Node(int num);
        void addValue(int num);
    private: 
        int value_l;
        int value_m;
        int value_r;
        B_Node *ptr_l;
        B_Node *ptr_ml;
        B_Node *ptr_mr;
        B_Node *ptr_r;
        bool isLeaf;
        int top_leaf;
        int bottom_leaf;
};