#include<iostream>
#include <memory>

// 全局共享指针容器（实际项目建议封装为类）
namespace GlobalHolder {
    template <typename T>
    struct Holder {
        static std::vector<std::shared_ptr<T>> pool; // 存储所有分配的内存
    };

    template <typename T>
    std::vector<std::shared_ptr<T>> Holder<T>::pool;
}

// 分配内存并返回裸指针（内存由全局容器托管）也就是说由此分配的空间不手动释放会持续到程序结束
#define AM AllocateMemory
template <typename T, typename... Args>
T* AllocateMemory(Args&&... args) {
    auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
    GlobalHolder::Holder<T>::pool.push_back(ptr); // 存入全局容器
    return ptr.get(); // 返回裸指针
}

// 手动释放内存（可选）
template <typename T>
void release_memory(T* target) {
    auto& pool = GlobalHolder::Holder<T>::pool;
    auto it = std::remove_if(pool.begin(), pool.end(),
        [target](const std::shared_ptr<T>& ptr) { return ptr.get() == target; });
    pool.erase(it, pool.end()); // 从容器移除，若无其他引用则内存自动释放
}