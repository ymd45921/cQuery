/**
 *
 * 新版 CLion 和新的 Rider 主题，当然要配上新的代码风格和快读板子了！
 * UPD: 2021-04-08 20:16:53
 */
#include <bits/stdc++.h>

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

static class cquery {

    static constexpr char _blank[] = " \n";
    static constexpr char _break[] = "\n";

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

    template <class T>
    static void write(FILE *io, T x)
    {
        if (x < 0) { fputc('-', io); x = -x; }
        static char str[40]; int cnt = 0;
        while (x > 9) { str[cnt ++] = (x % 10) + 48; x /= 10;}
        str[cnt ++] = x + 48;
        while (cnt --) fputc(str[cnt], io);
    }

    static void write(FILE *io, const char *const x) { fputs(x, io); }

    static void write(FILE *io, char *const x) { fputs(x, io); }

    static void write(FILE *io, std::string &x) { write(io, x.c_str()); }

    static void write(FILE *io, const char x) { fputc(x, io); }

    template <const char * charset>
    static inline bool is(int x) {
        const char *syb = charset;
        for (; *syb; ++ syb) if (*syb == x) return true;
        return false;
    }

    template <class T, class ...Ts>
    void write(FILE *io, T x, Ts ...xs) {
        write(io, x), write(io, xs...);
    }

    template <class T>
    void trace(FILE *io, const char *name, T &&object) {
        fprintf(io, "%s = ", name), write(io, object);
    }

    template <class T, class ...Ts>
    void trace(FILE *io, const char *names, T &&first, Ts &&...list) {
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

    template<class T, class... Ts>
    cquery &operator()(T &&x, Ts &&... y) {
        return (*this)(x), (*this)(y...);
    }

    cquery &operator()(char *x) {
        scanf("%s", x);
        return *this;
    }

    cquery &operator()(char &x) {
        do x = (char) ::getchar(); while (is<_blank>(x));
        return *this;
    }

    int nextInt() { return read<int>(); }

    auto nextLong() { return read<long long>(); }

    auto next128() { return read<__int128>(); }

    char getchar() {
        char x;
        (*this)(x);
        return x;
    }

    cquery &flush() { return flush(stdout), *this; }

    bool hasNext() { return this, !eof(stdin); }

    cquery &clear() { return cls(stdin), *this; }

    template <class T>
    cquery &print(T x) { return write(stdout, x), *this; }

    template <class T, class ...Ts>
    cquery &print(T x, Ts ...xs) {
        return write(stdout, x, xs...), *this;
    }

    template <class T>
    cquery &println(T x) {
        return write(stdout, x, '\n'), *this;
    }

    template <class T, class ...Ts>
    cquery &println(T x, Ts ...xs) {
        return write(stdout, x, xs..., '\n'), *this;
    }

    template <class T>
    cquery &put(T x) {
        return write(stdout, x, '\n'), *this;
    }

    template <class T, class ...Ts>
    cquery &put(T x, Ts ...xs) {
        write(stdout, x, ' '), put(xs...);
        return *this;
    }

    template <class T>
    cquery &nextArray(T *first, T *last) {
        while (first != last)
            (*this)(*first), ++ first;
        return *this;
    }

    template <class T, class comma = char>
    cquery &putArray(T *first, T *last, comma split = ' ') {
        while (first != last) {
            write(stdout, *first), ++ first;
            if (first != last) write(stdout, split);
            else write(stdout, '\n');
        }
        return *this;
    }
} $;

class buffered_reader {

    static constexpr char _blank[] = " \n";
    static constexpr char _break[] = "\n";

    static constexpr size_t buffer_size = 1e6;
    static char buffer[buffer_size];
    char *ptr = buffer, *eof = buffer;

    static size_t load_buffer(FILE *s) {
        return fread(buffer, sizeof(char), buffer_size, s);
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
        return f ? ret : -ret;
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
        if (ptr == eof) {
            ptr = buffer;
            eof = ptr + load_buffer(stdin);
        }
        return ptr == eof ? EOF : *ptr++;
    }

    int nextInt() { return parser<int>(); }
    auto nextLong() { return parser<long long>(); }
    auto next128() { return parser<__int128>(); }

} input;

using namespace std;

using longs = long long;
using uint = unsigned;
using lll = __int128;

const auto null = nullptr;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

    int a = input.nextInt();
    cout << a << endl;

    return 0;
}
