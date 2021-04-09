/**
 *
 * 新版 CLion 和新的 Rider 主题，当然要配上新的代码风格和快读板子了！
 * UPD: 2021-04-08 20:16:53
 *
 * 一些考据：
 * - to_string() 内部调用和 sprintf 一样，效率不优
 * - C++11 stod() 等系列方法，将 std::string 转化为对应类型
 * - strtod() 等系列方法在 stdlib 中，更加安全（但未必高效
 * - gcvf() 系列方法只能转化 double，且数字位数是精度位数不是小数点后
 * UPD: 2021-04-09 17:59:19
 */
#include <bits/stdc++.h>

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

static class cquery {

    static constexpr char _blank[] = " \n";
    static constexpr char _break[] = "\n";
    static constexpr size_t buffer_size = 100;
    static char buffer[buffer_size];
    static int fixed;

    template<class T>
    inline T read() {
        T ret = 0;
        int f = 0, ch = ::getchar();
        for (; !isdigit(ch); ch = ::getchar())
            if (ch == '-') f = !f;
        for (; isdigit(ch); ch = ::getchar())
            ret = ret * 10 + ch - 48;
        return f ? -ret : ret;
    }

    template<class T>
    inline T readRadix(int radix) {
        T ret = 0;
        int f = 0, ch = ::getchar(), d;
        while (toDigit(ch) < 0) {
            if (ch == '-') f = !f;
            ch = ::getchar();
        }
        while ((d = toDigit(ch)) >= 0)
            ret = ret * radix + d, ch = ::getchar();
        return f ? -ret : ret;
    }

    static inline auto parse() {
        readToken();
        auto ret = _atoi64(buffer);
        return ret;
    }

    static inline auto parse(int value, int radix = 10) {
        return itoa(value, buffer, radix), buffer;
    }

    template<class T>
    static void write(FILE *io, const T &x) {
        if (x < 0) {
            fputc('-', io);
            x = -x;
        }
        static char *str = buffer;
        int cnt = 0;
        while (x > 9) {
            str[cnt++] = (x % 10) + 48;
            x /= 10;
        }
        str[cnt++] = x + 48;
        while (cnt--) fputc(str[cnt], io);
    }

    template<class T>
    static void write(FILE *io, const T &&x) { write(io, x); }

    static void write(FILE *io, const double x) {
        write(io, gcvt(x, fixed, buffer));
    }

    [[deprecated]]
    static void write(FILE *io, const long double x) {
        sprintf(buffer, "%Lf", x), write(io, buffer);
    }

    static void write(FILE *io, const float x) { write(io, (double)x); }

    static void write(FILE *io, const char *const x) { fputs(x, io); }

    static void write(FILE *io, char *const x) { fputs(x, io); }

    static void write(FILE *io, const std::string &x) { write(io, x.c_str()); }

    static void write(FILE *io, const char x) { fputc(x, io); }

    template<const char *charset>
    static inline bool is(int x) {
        if (x <= 0) return true;
#ifndef WIN64
        const char *syb = charset;
        for (; *syb; ++syb) if (*syb == x) return true;
        return false;
#else   // TODO: 使用 x86 SIMD(SSE) 指令集进行硬件优化
        const char *syb = charset;
        for (; *syb; ++syb) if (*syb == x) return true;
        return false;
#endif
    }

    static inline int toDigit(int x) {
        if (x > 0)
            if (isdigit(x)) return x - 48;
            else if (x >= 'a' && x <= 'f') return x - 51;
            else if (x >= 'A' && x <= 'F') return x - 31;
            else return -1;
        else return -1;
    }

    template<class T, class ...Ts>
    void write(FILE *io, const T &x, Ts ...xs) {
        write(io, x), write(io, xs...);
    }

    template<class T, class ...Ts>
    void write(FILE *io, const T &&x, Ts ...xs) {
        write(io, x), write(io, xs...);
    }

    static char* readToken() {
        char *cur = buffer;
        int ch = ::getchar();
        while (is<_blank>(ch)) ch = ::getchar();
        for (; !is<_blank>(ch); ch = ::getchar())
            *cur++ = (char) ch;
        return *cur = '\0', cur;
    }

    template<class T>
    void trace(FILE *io, const char *name, T &&object) {
        fprintf(io, "%s = ", name), write(io, object);
    }

    template<class T, class ...Ts>
    void trace(FILE *io, const char *names, T &&first, Ts ...list) {
        const char *separate = strchr(names + 1, ',');
        fwrite(names, sizeof(char), separate - names, io);
        write(io, " = ", first, ", ");
        trace(io, separate + 1, list...);
    }

    static void flush(FILE *stream) { fflush(stream); }

    static int eof(FILE *stream) { return feof(stream); }

    static void cls(FILE *stream) { clearerr(stream); }

public:

    template<class T>
    cquery &operator()(T &x) {
        x = read<T>();
        return *this;
    }

    template<class T, class... Ts>
    cquery &operator()(T &x, Ts &... y) {
        return (*this)(x), (*this)(y...);
    }

    cquery &operator()(char *x) {
        scanf("%s", x);
        return *this;
    }

    cquery &operator()(double &x) {
        auto end = readToken();
        x = strtod(buffer, &end);
        return *this;
    }

    cquery &operator()(long double &x) {
        auto end = readToken();
        x = strtold(buffer, &end);
        return *this;
    }

    cquery &operator()(float &x) {
        auto end = readToken();
        x = strtof(buffer, &end);
        return *this;
    }

    cquery &operator()(char &x) {
        do x = (char) ::getchar(); while (is<_blank>(x));
        return *this;
    }

    template <class T>
    T next() {
        T ret;
        (*this)(ret);
        return ret;
    }

    int nextInt() { return read<int>(); }

    int nextInt(int radix) { return readRadix<int>(radix); }

    auto nextLong() { return read<long long>(); }

    auto nextLong(int radix) { return readRadix<long long>(radix); }

    auto next128() { return read<__int128>(); }

    char getchar() { return next<char>(); }

    double nextDouble() { return next<double>(); }

    auto nextFloat() { return next<float>(); }

    cquery &flush() { return flush(stdout), *this; }

    bool hasNext() { return this, !eof(stdin); }

    cquery &clear() { return cls(stdin), *this; }

    template<class T>
    cquery &print(const T &x) { return write(stdout, x), *this; }

    template<class T>
    cquery &print(const T &&x) { return write(stdout, x), *this; }

    template<class T, class ...Ts>
    cquery &print(T &x, Ts ...xs) {
        return write(stdout, x, xs...), *this;
    }

    template<class T, class ...Ts>
    cquery &print(T &&x, Ts ...xs) {
        return write(stdout, x, xs...), *this;
    }

    template<class T>
    cquery &println(const T &x) {
        return write(stdout, x, '\n'), *this;
    }

    template<class T>
    cquery &println(const T &&x) {
        return write(stdout, x, '\n'), *this;
    }

    template<class T, class ...Ts>
    cquery &println(const T &x, Ts ...xs) {
        return write(stdout, x, xs..., '\n'), *this;
    }

    template<class T, class ...Ts>
    cquery &println(const T &&x, Ts ...xs) {
        return write(stdout, x, xs..., '\n'), *this;
    }

    template<class T>
    cquery &put(const T &x) {
        return write(stdout, x, '\n'), *this;
    }

    template<class T>
    cquery &put(const T &&x) {
        return write(stdout, x, '\n'), *this;
    }

    template<class T, class ...Ts>
    cquery &put(const T &x, Ts ...xs) {
        write(stdout, x, ' '), put(xs...);
        return *this;
    }

    template<class T, class ...Ts>
    cquery &put(const T &&x, Ts ...xs) {
        write(stdout, x, ' '), put(xs...);
        return *this;
    }

    template<class T>
    cquery &nextArray(T first, T last) {
        while (first != last)
            (*this)(*first), ++first;
        return *this;
    }

    template<class T, class comma = char>
    cquery &putArray(T first, T last, comma split = ' ') {
        while (first != last) {
            write(stdout, *first), ++first;
            if (first != last) write(stdout, split);
            else write(stdout, '\n');
        }
        return *this;
    }

    cquery &setDigits(int n) { return fixed = n, *this; }
} $;

char cquery::buffer[cquery::buffer_size];
int cquery::fixed = 18;

class buffered_reader {

    static constexpr char _blank[] = " \n";
    static constexpr char _break[] = "\n";

    static constexpr size_t buffer_size = 10;
    static char buffer[buffer_size];
    char *ptr = buffer, *eof = buffer;

    static size_t load_buffer(FILE *s) {
        return fread(buffer, sizeof(char), buffer_size, s);
    }
    
    void refresh_buffer() {
        if (ptr == eof) {
            ptr = buffer;
            eof = ptr + load_buffer(stdin);
        }
    }

    template <const char * charset>
    static inline bool is(int x) {
        const char *syb = charset;
        for (; *syb; ++ syb) if (*syb == x) return true;
        return false;
    }

    template <class integer>
    integer parser() {
        integer ret = 0;
        int f = 0, ch = getchar();
        while (!isdigit(ch)) {
            if (ch == '-') f = !f;
            ch = getchar();
        }
        while (isdigit(ch)) {
            ret = ret * 10 + ch - 48;
            ch = getchar();
        }
        return f ? -ret : ret;
    }

    template <>
    char parser() { return (char)getchar(); }

    template <class integer>
    integer parser(int radix) {
        integer ret = 0;
        int f = 0, ch = getchar(), d;
        while (digit(ch) < 0) {
            if (ch == '-') f = !f;
            ch = getchar();
        }
        while ((d = digit(ch)) > 0)
            ret = ret * 10 + d, ch = getchar();
        return f ? -ret : ret;
    }
    
    static int digit(int x) {
        if (x > 0)
            if (isdigit(x)) return x - 48;
            else if (x >= 'a' && x <= 'f') return x - 51;
            else if (x >= 'A' && x <= 'F') return x - 31;
            else return -1;
        else return -1;
    }

public:
    buffered_reader() = default;

    auto &reset() { return rewind(stdin), *this; }

    [[deprecated]] const char *nextToken() {
        char *head = ptr, *last = ptr;
        while (!is<_blank>(*last)) ++ last;
        *last = '\0', ++ last;
        return head;
    }

    [[deprecated]] const char *nextLine() {
        char *head = ptr, *last = ptr;
        while (!is<_break>(*last)) ++ last;
        *last = '\0', ++ last;
        return head;
    }

    int getchar() {
        refresh_buffer();
        return ptr == eof ? EOF : *ptr++;
    }
    
    int peek() {
        refresh_buffer();
        return ptr == eof ? EOF : *ptr;
    }
    
    bool hasNext() { return peek() != EOF; }

    int nextInt() { return parser<int>(); }
    auto nextLong() { return parser<long long>(); }
    auto next128() { return parser<__int128>(); }

    int nextInt(int radix) { return parser<int>(radix); }
    auto nextLong(int radix) { return parser<long long>(radix); }
    auto next128(int radix) { return parser<__int128>(radix); }

    template <class T>
    auto &operator()(T &x) { return x = parser<T>(), *this; }
    template <class T, class ...Ts>
    auto &operator()(T &x, Ts ...xs) { return x = parser<T>(), (*this)(xs...); }
    
    template <class T>
    auto &operator, (T &x) { return x = parser<T>(), *this; }

} input;

char buffered_reader::buffer[];

using namespace std;

using longs = long long;
using uint = unsigned;
using lll = __int128;

const auto null = nullptr;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);
    

    return 0;
}
