def s_expression_eval(sexp):
    def operand_dict(operand, operator_left, operator_right):
        return { '+': optr_left + optr_right,
                 '-': optr_left - optr_right,
                 '*': optr_left * optr_right,
                 '/': optr_left / optr_right,
                 '%': optr_left % optr_right,
                 '^': optr_left ** optr_right}[operand]
    stack, tmp = [], ''
    for s in sexp:
        if s=='(': 
            pass 
        elif s in ('+', '-', '*', '/',  '^', '%', '||'):
            stack  += s[0], 
        elif s.isnumeric():
            tmp += s
        elif s==',':
            if tmp: stack += int(tmp),; tmp = ''
        elif s==')':
            if tmp: stack += int(tmp),; tmp = ''
            optr_right = stack.pop()
            optr_left = stack.pop()
            stack += operand_dict(stack.pop(), optr_left, optr_right),
        else: pass
    return stack[0]
print(s_expression_eval('(+,12,(/,(*,20,3),5))'))
