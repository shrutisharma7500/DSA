class Solution {
public:
    bool isNumber(string s) {
        bool seenDigit = false;
        bool seenDot = false;
        bool seenExp = false;

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            if (isdigit(c)) {
                seenDigit = true;
            }
            else if (c == '+' || c == '-') {
                // Sign allowed only at start or just after exponent
                if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E')
                    return false;
            }
            else if (c == '.') {
                // Dot allowed only once and not after exponent
                if (seenDot || seenExp)
                    return false;
                seenDot = true;
            }
            else if (c == 'e' || c == 'E') {
                // Exponent rules
                if (seenExp || !seenDigit)
                    return false;
                seenExp = true;
                seenDigit = false; // reset, need digits after exponent
            }
            else {
                return false; // invalid character
            }
        }

        return seenDigit;
    }
};
