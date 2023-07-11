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

//验证subscribe即为开启一个线程的测试代码
class DynamicReconfigureClient {
public:
    bool flag = false;

    DynamicReconfigureClient() {

        auto id = new std::thread(&DynamicReconfigureClient::func, this, nullptr);
        while (flag == false) {
            cout << "wait" << endl;
            waitKey(10000);
        }

        cout << "finally jump out of the loop!!!!" << endl;
    }

    void func(int *val) {
        int n{0};
        while (n++ < 3) {
            cout << "new thread: " << n << endl;
        }

        flag = true;
    }
};
