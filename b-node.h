class B_Node {
    public: 
        B_Node(int num, bool leaf);
        void addValue(int num);
        void set_l(B_Node *node);
        void set_ml(B_Node *node);
        void set_mr(B_Node *node);
        void set_r(B_Node *node);
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