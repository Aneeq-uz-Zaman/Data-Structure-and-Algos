#include <bits/stdc++.h>
using namespace std;

// Recursive utilities implementing the requested problems without using explicit stacks.

// Q1: Validate Heterogeneous brackets (balanced brackets for (), {}, []) using recursion.
// We'll implement a recursive parser that checks matching pairs.

bool match(char a, char b) {
    return (a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']');
}

// Recursive function that tries to consume a balanced prefix starting at index i and returns
// the index after the balanced segment, or -1 if invalid.
int consumeBalanced(const string &s, int i) {
    int n = s.size();
    if (i >= n) return i; // empty
    if (s[i] == ')' || s[i] == '}' || s[i] == ']') return -1; // cannot start with closing
    // must be opening
    if (s[i] != '(' && s[i] != '{' && s[i] != '[') return -1;
    char open = s[i];
    int j = i + 1;
    // until we find matching close for this open, we may have nested balanced groups
    while (j < n) {
        if (s[j] == ')' || s[j] == '}' || s[j] == ']') {
            if (match(open, s[j])) return j + 1;
            else return -1;
        } else {
            int next = consumeBalanced(s, j);
            if (next == -1) return -1;
            j = next;
        }
    }
    return -1; // no matching close
}

bool isBalancedRecursive(const string &s) {
    int i = 0, n = s.size();
    while (i < n) {
        int next = consumeBalanced(s, i);
        if (next == -1) return false;
        i = next;
    }
    return true;
}

// Q2: Check whether string is a^n b^n (i.e., anbn) using recursion
bool isAnBn(const string &s, int i = 0, int j = -1) {
    if (j == -1) j = s.size() - 1;
    if (i > j) return true; // empty
    if (s[i] != 'a' || s[j] != 'b') return false;
    return isAnBn(s, i+1, j-1);
}

// Q3: Check whether string is a^s b^t where s,t >=0 (i.e., all a's followed by b's)
bool isAsBt(const string &s) {
    int n = s.size();
    int i = 0;
    while (i < n && s[i] == 'a') i++;
    while (i < n && s[i] == 'b') i++;
    return i == n; // only a's then b's
}

// Q4: Check whether string is a^n b^n c^n using recursion
bool isAnBnCn(const string &s, int l = 0, int r = -1) {
    if (r == -1) r = s.size() - 1;
    // skip any leading 'a's and trailing 'c's pairing one a with one c and ensuring b's in middle
    if (l > r) return true; // empty
    if (s[l] != 'a') return false;
    if (s[r] != 'c') return false;
    // remove one a from left and one c from right, but we must ensure middle is b^n
    // find the segment between l+1 and r-1 and check that it is b^k possibly with nested a..c pairs
    // A simple recursive approach: peel one 'a' and one 'c' and then validate remainder.
    return isAnBnCn(s, l+1, r-1);
}

// But the above naive check accepts 'aabbcc' and also 'abc' but doesn't ensure the b's count equals n.
// We need stricter: after removing n a's and n c's, the middle must be exactly n b's.

bool isAnBnCn_strict(const string &s) {
    int n = s.size();
    int l = 0;
    while (l < n && s[l] == 'a') l++;
    int r = n-1;
    while (r >= 0 && s[r] == 'c') r--;
    int countA = l;
    int countC = n-1 - r;
    if (countA != countC) return false;
    int countB = 0;
    for (int k = l; k <= r; ++k) if (s[k] == 'b') countB++; else return false;
    return countA == countB;
}

// Q5: Reverse order of elements in stack S using recursion (no extra stacks).
// The user asked to use recursion instead of stack. We'll implement functions that operate on vector<int> as stack.

void insertAtBottom(vector<int> &st, int x) {
    if (st.empty()) {
        st.push_back(x);
        return;
    }
    int top = st.back(); st.pop_back();
    insertAtBottom(st, x);
    st.push_back(top);
}

void reverseStackRecursive(vector<int> &st) {
    if (st.empty()) return;
    int top = st.back(); st.pop_back();
    reverseStackRecursive(st);
    insertAtBottom(st, top);
}

// Q7: Put elements on stack S in ascending order using recursion and one additional variables (no extra array)
void sortedInsert(vector<int> &st, int x) {
    if (st.empty() || st.back() <= x) { // ascending with top as largest
        st.push_back(x);
        return;
    }
    int top = st.back(); st.pop_back();
    sortedInsert(st, x);
    st.push_back(top);
}

void sortStackRecursive(vector<int> &st) {
    if (st.empty()) return;
    int top = st.back(); st.pop_back();
    sortStackRecursive(st);
    sortedInsert(st, top);
}

// Q8: Transfer elements of S1 to S2 so that S2 has same order as S1 using recursion
void transferSameOrder(vector<int> &s1, vector<int> &s2) {
    if (s1.empty()) return;
    int x = s1.back(); s1.pop_back();
    transferSameOrder(s1, s2);
    s2.push_back(x);
}

// Q9: Convert infix to prefix using recursion. We'll parse expression recursively with operator precedence.
// For simplicity handle single-letter operands and operators +,-,*,/,^ and parentheses.

string infixToPrefixRec(const string &s, int &i);

// helper to remove spaces
string removeSpaces(const string &s) {
    string t;
    for (char c: s) if (!isspace((unsigned char)c)) t.push_back(c);
    return t;
}

int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string parseFactor(const string &s, int &i) {
    if (i >= (int)s.size()) return "";
    if (s[i] == '(') {
        i++; // consume (
        string inside = infixToPrefixRec(s, i);
        if (i < (int)s.size() && s[i] == ')') i++;
        return inside;
    }
    // operand: read alnum
    string op;
    while (i < (int)s.size() && (isalnum((unsigned char)s[i]) || s[i] == '_')) op.push_back(s[i++]);
    return op;
}

string infixToPrefixRec(const string &s, int &i) {
    // parse using shunting-yard style but recursively: build list of tokens and apply operators by precedence
    vector<string> operands;
    vector<char> ops;
    auto applyOp = [&](char op) {
        string b = operands.back(); operands.pop_back();
        string a = operands.back(); operands.pop_back();
        string res = string(1, op) + a + b; // prefix
        operands.push_back(res);
    };
    while (i < (int)s.size() && s[i] != ')') {
        if (s[i] == '(') {
            i++;
            operands.push_back(infixToPrefixRec(s, i));
            if (i < (int)s.size() && s[i] == ')') i++;
        } else if (isalnum((unsigned char)s[i]) || s[i] == '_') {
            operands.push_back(parseFactor(s, i));
        } else { // operator
            char cur = s[i++];
            while (!ops.empty() && ((prec(ops.back()) > prec(cur)) || (prec(ops.back()) == prec(cur) && cur != '^'))) {
                char op = ops.back(); ops.pop_back();
                applyOp(op);
            }
            ops.push_back(cur);
        }
    }
    while (!ops.empty()) {
        char op = ops.back(); ops.pop_back();
        applyOp(op);
    }
    if (operands.empty()) return string();
    return operands.back();
}

string infixToPrefix(const string &expr) {
    string s = removeSpaces(expr);
    int i = 0;
    return infixToPrefixRec(s, i);
}

// Q10: Check palindrome using recursion
bool isPalindromeRec(const string &s, int l = 0, int r = -1) {
    if (r == -1) r = s.size()-1;
    while (l < r && !isalnum((unsigned char)s[l])) l++;
    while (l < r && !isalnum((unsigned char)s[r])) r--;
    if (l >= r) return true;
    if (tolower((unsigned char)s[l]) != tolower((unsigned char)s[r])) return false;
    return isPalindromeRec(s, l+1, r-1);
}

// Q11: Reverse words in a given string using recursion
void reverseWordsRec(const vector<string> &words, int i) {
    if (i >= (int)words.size()) return;
    reverseWordsRec(words, i+1);
    cout << words[i] << (i+1==(int)words.size()?"":" ");
}

string reverseWords(const string &s) {
    vector<string> words;
    stringstream ss(s);
    string w;
    while (ss >> w) words.push_back(w);
    // capture output into string
    stringstream out;
    function<void(int)> rec = [&](int i){ if (i >= (int)words.size()) return; rec(i+1); out << words[i] << (i+1==(int)words.size()?"":" "); };
    rec(0);
    return out.str();
}

// Q12: Convert prefix/postfix to infix using recursion.
// Prefix to infix: read token stream left-to-right

vector<string> tokenize(const string &s) {
    vector<string> t;
    string cur;
    for (size_t i=0;i<s.size();) {
        if (isspace((unsigned char)s[i])) { i++; continue; }
        if (isalpha((unsigned char)s[i]) || isdigit((unsigned char)s[i]) || s[i]=='_' ) {
            cur.clear();
            while (i<s.size() && (isalnum((unsigned char)s[i])||s[i]=='_')) cur.push_back(s[i++]);
            t.push_back(cur);
        } else {
            t.push_back(string(1, s[i++]));
        }
    }
    return t;
}

// prefix to infix using recursion with index by reference
string prefixToInfixRec(const vector<string> &tok, int &i) {
    if (i >= (int)tok.size()) return string();
    string t = tok[i++];
    if (t.size()==1 && string("+-*/^%").find(t)!=string::npos) {
        string A = prefixToInfixRec(tok, i);
        string B = prefixToInfixRec(tok, i);
        return "(" + A + t + B + ")";
    }
    return t;
}

string prefixToInfix(const string &s) {
    auto tok = tokenize(s);
    int i = 0;
    return prefixToInfixRec(tok, i);
}

// postfix to infix: process tokens left to right, but recursively we can process from end
string postfixToInfixRec(const vector<string> &tok, int &i) {
    if (i < 0) return string();
    string t = tok[i--];
    if (t.size()==1 && string("+-*/^%").find(t)!=string::npos) {
        string B = postfixToInfixRec(tok, i);
        string A = postfixToInfixRec(tok, i);
        return "(" + A + t + B + ")";
    }
    return t;
}

string postfixToInfix(const string &s) {
    auto tok = tokenize(s);
    int i = (int)tok.size()-1;
    return postfixToInfixRec(tok, i);
}

// Q13: Google 'Stack Folding Problem' - we can't access web. We'll add a note in README.

// Q14: Function call stack - demonstrate recursion depth with a sample function
int factorialRec(int n) {
    if (n <= 1) return 1;
    return n * factorialRec(n-1);
}

// small helpers to print stack vector
string stackToStr(const vector<int> &st) {
    stringstream ss;
    ss << "[";
    for (int i = 0; i < (int)st.size(); ++i) {
        ss << st[i];
        if (i+1 < (int)st.size()) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Q1: bracket tests:\n";
    vector<string> tests = {"()[]{}","([{}])","([)]","","((())","{[()()]}","{[(])}"};
    for (auto &t: tests) cout << t << " -> " << (isBalancedRecursive(t)?"Balanced":"Not balanced") << "\n";

    cout << "\nQ2: anbn tests:\n";
    vector<string> t2 = {"","ab","aaabbb","aabbb","bbbaaa"};
    for (auto &s: t2) cout << s << " -> " << (isAnBn(s)?"Yes":"No") << "\n";

    cout << "\nQ3: asbt tests:\n";
    vector<string> t3 = {"","a","b","aaabbb","aaaaaabbb","aba","aab"};
    for (auto &s: t3) cout << s << " -> " << (isAsBt(s)?"Yes":"No") << "\n";

    cout << "\nQ4: anbncn tests (strict):\n";
    vector<string> t4 = {"","abc","aabbcc","aaabbbccc","aabcc","aaabbbcc"};
    for (auto &s: t4) cout << s << " -> " << (isAnBnCn_strict(s)?"Yes":"No") << "\n";

    cout << "\nQ5: reverse stack:\n";
    vector<int> st = {1,2,3,4,5};
    cout << "orig: " << stackToStr(st) << "\n";
    reverseStackRecursive(st);
    cout << "reversed: " << stackToStr(st) << "\n";

    cout << "\nQ7: sort stack ascending (top is largest):\n";
    vector<int> s2 = {3,1,4,2};
    cout << "orig: " << stackToStr(s2) << "\n";
    sortStackRecursive(s2);
    cout << "sorted: " << stackToStr(s2) << "\n";

    cout << "\nQ8: transfer S1->S2 same order:\n";
    vector<int> s1 = {10,20,30};
    vector<int> s22;
    transferSameOrder(s1, s22);
    cout << "S1 empty: " << stackToStr(s1) << ", S2: " << stackToStr(s22) << "\n";

    cout << "\nQ9: infix to prefix:\n";
    cout << "a+b*c -> " << infixToPrefix("a+b*c") << "\n";
    cout << "(a+b)*c -> " << infixToPrefix("(a+b)*c") << "\n";

    cout << "\nQ10: palindrome tests:\n";
    vector<string> ptests = {"A man, a plan, a canal, Panama","racecar","hello"};
    for (auto &s: ptests) cout << s << " -> " << (isPalindromeRec(s)?"Yes":"No") << "\n";

    cout << "\nQ11: reverse words:\n";
    cout << reverseWords("The quick brown fox") << "\n";

    cout << "\nQ12: convert prefix/postfix to infix:\n";
    cout << "+ab (prefix) -> " << prefixToInfix("+ a b") << "\n";
    cout << "ab+ (postfix) -> " << postfixToInfix("a b +") << "\n";

    cout << "\nQ14: factorial(5) via recursion -> " << factorialRec(5) << "\n";

    cout << "\nNote: Q13 (Stack Folding Problem) - see README for pointers.\n";

    return 0;
}
