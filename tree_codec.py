"""
 deserialize a string into a tree:
     "1(2,3(4,5))" =>
        1
      /   \
     2     3
         /  \
        4    5
 and serialize the output tree, 
 get the string "1(2,3(4,5))"
"""    
class tree_node :
    def __init__(self, val):
        self._v = val
        self.left = None
        self.right = None

def serialize(root):
    ans = ''
    if root:
        ans += str(root._v)
        if not root.left is root.right:
            ans += '('
            if root.left:
                ans += serialize(root.left)
            if root.right:
                ans += ','
                ans += serialize(root.right)
            ans += ')'
    return ans
def deserialize(s):
    """
    input: s : str
    rtype tree_node
    """
    stack, tree_body = [(tree_node(-1), 0)], [tree_node(-1)]
    in_parsing_num = False
    idx, tmpi, prev =1, '', '('
    for c in s:
        if c.isnumeric():
            tmpi += c
            if not in_parsing_num:
                in_parsing_num = True
        elif c in ('(', ')', ','):
            in_parsing_num = False
            if tmpi:
                node = tree_node(int(tmpi))
                tree_body += node,

                j = stack[-1][1]
                if c == '(':
                    stack += (node, idx), # this is a parent node
                    #idx += 1
                    if prev == '(':                # (123(
                        tree_body[j].left  = node
                    elif prev == ',':              # ,123(
                        tree_body[j].right = node
                    else: # ')'
                        raise Exception("Wrong input ")
                else:  # ')'  ','
                    if prev == '(':                # (123)  (123,
                        tree_body[j].left  = node
                        if c == ')':
                            stack.pop()   # 111(123)
                    elif prev == ',' and c == ')': # ,123)
                        tree_body[j].right = node
                        stack.pop()
                    else: # ')'                    # )123)  )123,  ,123,
                        raise Exception("Wrong input since ")
                idx += 1
                tmpi = ''
            else:  # tmpi == ''
                if prev == ')' and c == ')':  #  ))
                    stack.pop()
                elif prev in (')', '(') and c ==','   :  pass  # ), (, 
                else:                # ((  )(  ,(   ,,  ,)  ()
                    raise Exception("Wrong input since ")
            prev = c
        else: pass
    return tree_body[1:] 
s = "111(21(,33(1,23(,44))),3(,66(1,23)))"
ans = deserialize(s)
ss = serialize(ans[0])
assert(ss==s)


