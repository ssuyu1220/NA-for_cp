#include <string.h>
#include <ctype.h>
#include <lber.h>

int check_password(const char *pPasswd, void *pEntry, struct berval *pErrmsg, struct berval *pArg) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    size_t len = strlen(pPasswd);

    static const char *msg_class = "Password must include at least 3 of: upper, lower, digit, special characters";

    for (size_t i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char)pPasswd[i];
        if (isupper(ch)) has_upper = 1;
        if (islower(ch)) has_lower = 1;
        if (isdigit(ch)) has_digit = 1;
        if (!isupper(ch) && !islower(ch) && !isdigit(ch)) has_special = 1;
    }

    int classes = has_upper + has_lower + has_digit + has_special;
    if (classes < 3) {
        if (pErrmsg) {
            pErrmsg->bv_val = (char *)msg_class;
            pErrmsg->bv_len = strlen(msg_class);
        }
        return 1;
    }

    return 0;
}

int init_module(int argc, char *argv[]) {
    return 0;
}
