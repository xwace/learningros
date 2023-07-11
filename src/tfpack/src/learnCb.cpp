template<class M, class T>
struct nodeHandle {
    void subscribe(void(T::*fp)(const std::shared_ptr<M const> &), T *obj) {
        std::shared_ptr<int const> val(new int(17));
        auto callback = std::bind(&T::callback, obj, placeholders::_1);
        callback(val);
    }
};

struct Client {
    Client() {
        nodeHandle<int, Client> nh;
        nh.subscribe(&Client::callback, this);
    }

    void callback(const std::shared_ptr<int const> &val) {
        cout << "val: " << *val << endl;
    }
};
