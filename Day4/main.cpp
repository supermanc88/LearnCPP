#include <iostream>


int test_unique_ptr() {
    std::unique_ptr<int> a = std::make_unique<int>(42);
    std::cout << "Unique Pointer Value: " << *a << std::endl;

    // set a value
    *a = 100;
    std::cout << "Updated Unique Pointer Value: " << *a << std::endl;

    std::unique_ptr<int []> array = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        array[i] = i * 10;
    }
    std::cout << "Unique Pointer Array Values: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::unique_ptr<int> b = std::move(a);
    if (!a) {
        std::cout << "a is now nullptr after move." << std::endl;
    }
    std::cout << "b Value after move: " << *b << std::endl;

    return 0;
}

int test_shared_ptr() {
    std::shared_ptr<int> a = std::make_shared<int>(55);
    std::cout << "Shared Pointer Value: " << *a << std::endl;
    std::cout << "Reference Count: " << a.use_count() << std::endl;

    {
        std::shared_ptr<int> b = a;
        std::cout << "Inside block - Shared Pointer b Value: " << *b << std::endl;
        std::cout << "Inside block - Reference Count: " << a.use_count() << std::endl;
        std::cout << "Inside block - b Reference Count: " << b.use_count() << std::endl;
    }

    std::cout << "Outside block - Reference Count: " << a.use_count() << std::endl;

    return 0;
}

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // weak_ptr to prevent cyclic reference
};

int test_weak_ptr() {

    std::shared_ptr<Node> NodeA = std::make_shared<Node>();
    std::shared_ptr<Node> NodeB = std::make_shared<Node>();

    std::cout << "NodeA use_count: " << NodeA.use_count() << std::endl; // 1
    std::cout << "NodeB use_count: " << NodeB.use_count() << std::endl; // 1

    NodeA->next = NodeB;
    NodeB->prev = NodeA; // weak_ptr does not increase reference count

    std::cout << "After linking:" << std::endl;
    std::cout << "NodeA use_count: " << NodeA.use_count() << std::endl; // 1
    std::cout << "NodeB use_count: " << NodeB.use_count() << std::endl; // 2


    return 0;
}


struct NodeClass {
    std::shared_ptr<NodeClass> next;  // 互相持有 shared_ptr
    std::string name;

    NodeClass(const std::string& n) : name(n) {
        std::cout << "Node " << name << " 构造\n";
    }

    ~NodeClass() {
        std::cout << "Node " << name << " 析构\n";
    }
};

int test_shared_ptr_cyclic_reference() {
    std::cout << "开始创建循环引用...\n";

    auto node1 = std::make_shared<NodeClass>("A");
    auto node2 = std::make_shared<NodeClass>("B");

    node1->next = node2;  // A 持有 B
    node2->next = node1;  // B 持有 A

    // 此时 node1 和 node2 的引用计数都是 2
    std::cout << "node1 use_count: " << node1.use_count() << '\n';
    std::cout << "node2 use_count: " << node2.use_count() << '\n';

    // 即使离开作用域，node1 和 node2 也不会被析构！
    std::cout << "main 结束，但 Node 不会析构！\n";
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    test_unique_ptr();
    std::cout << "------------------------" << std::endl;
    test_shared_ptr();
    std::cout << "------------------------" << std::endl;
    test_weak_ptr();
    std::cout << "------------------------" << std::endl;
    test_shared_ptr_cyclic_reference();

    return 0;
}