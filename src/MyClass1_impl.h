#pragma once
#include <mylib/MyClass1.h>

// ============================================================
//  MyClass1::Impl : 実装本体（配布しない内部ヘッダ）
//  - ここに置いたものはテストから直接・網羅的に検証できる。
//  - 配布物は include/ + .lib + .dll のみなので、この
//    ファイルの存在自体がユーザーからは見えない。
// ============================================================
namespace mylib {
namespace detail {

struct MyClass1Impl {
    // --- 旧・private メンバ変数 ---
    int total_ = 0;

    // --- public 相当の処理本体 ---
    void addScore(int value) { total_ += clamp(value); }
    int  total() const       { return total_; }

    // --- 旧・private メンバ関数 ---
    // 値を 0..100 に丸める
    int clamp(int value) const {
        if (value < 0)   return 0;
        if (value > 100) return 100;
        return value;
    }
};

} // namespace detail
} // namespace mylib
