#pragma once
#include "export.h"

// ============================================================
//  MyClass1 : スコアを蓄積するクラス（配布ヘッダ）
//  - ライブラリの機能のみを記述。テスト関連の記述は一切なし。
//  - 実装詳細は Impl に隠蔽（pimpl）。ABI 安定にも寄与。
// ============================================================
namespace mylib {

namespace detail { struct MyClass1Impl; }  // 実装の前方宣言（中身は非公開）

class MYLIB_API MyClass1 {
public:
    MyClass1();
    ~MyClass1();

    MyClass1(const MyClass1&) = delete;
    MyClass1& operator=(const MyClass1&) = delete;

    // --- public メンバ関数 ---
    // 値を 0..100 に丸めて加算する
    void addScore(int value);
    // これまでの合計を返す
    int  total() const;

private:
    // --- private メンバ変数 ---
    detail::MyClass1Impl* impl_;   // 実装本体（中身は配布物から見えない）
};

} // namespace mylib
