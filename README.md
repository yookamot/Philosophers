# Philosophers - 哲学者の食事問題

## 概要

- 複数の哲学者が円卓に座り、「考える」「食べる」「寝る」を繰り返すシミュレーション。
- 食事するには隣り合う2本のフォークを両方使う必要がある。
- フォークは哲学者の人数分あり、隣接する哲学者と共有する。
- 最後の食事から指定時間内に食べられなければ哲学者は「死亡」し、シミュレーションは終了する。
- 哲学者は互いに通信しない。
- 状態変化は決められたフォーマットでログに出力。

---

## 実行引数

number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
- `number_of_philosophers`: 哲学者の数（＝フォークの数）
- `time_to_die`: 最後の食事からこれだけのミリ秒以内に次の食事を開始しなければ死亡
- `time_to_eat`: 食事にかかるミリ秒
- `time_to_sleep`: 睡眠にかかるミリ秒
- `number_of_times_each_philosopher_must_eat`（任意）: これを満たしたらシミュレーション終了

---

## 動作ルール

- 各哲学者は番号1〜Nを持ち、哲学者1は哲学者Nの隣に座る。
- 哲学者は「考える→フォーク2本を取る→食べる→フォークを置く→寝る→考える」の順に繰り返す。
- フォークの状態はmutexやセマフォで保護し、同時アクセスを防止する。
- ログ出力は状態変化のたびに行い、出力の競合は避ける。
- 哲学者の死亡メッセージは死亡から10ms以内に出力する。
- データ競合やレースコンディションが起こらないようにする。

---

## 実装制約

- 各哲学者は個別のスレッドとして実装。
- フォークはmutexで管理。
- グローバル変数禁止。共有データは構造体などにまとめ、引数やポインタで管理。
- 使用可能関数例: `pthread_create`, `pthread_mutex_lock`, `usleep`, `gettimeofday` など。


---

## ログ出力形式

- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died
- `timestamp_in_ms`: シミュレーション開始からの経過時間（ミリ秒）
- `X`: 哲学者番号

---

## 提出物

- Mandatory part: `philo/` ディレクトリにソースとMakefileを提出。
- Bonus part: `philo_bonus/` ディレクトリにソースとMakefileを提出。
- Makefileは必須ルール（`all`, `clean`, `fclean`, `re`）を守ること。
- BonusはMandatoryを完璧に合格してから評価される。

---

## 注意事項

- グローバル変数禁止。
- メモリリーク・クラッシュ禁止。
- Norm（コード規約）厳守。
- ログ出力のフォーマット厳守。
- 同期処理・排他制御の正確な実装が必要。

---

## 参考

哲学者の食事問題は並行処理と排他制御の代表的課題です。  
mutexやセマフォを用いて、デッドロックや競合状態を避けながら安全に動作させることが求められます。

---

## まとめ

- 各哲学者はスレッド（またはプロセス）で動作。
- フォークはmutexまたはセマフォで管理。
- 状態はログに正確に出力。
- 全ての仕様を守りつつ、安定して動作するプログラムを作ること。

---

42Tokyo プロジェクト  
**「哲学者は死なせてはならない」**  
理論と実装の両方を通じて同期制御を深く理解しましょう。

