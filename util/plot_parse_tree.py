import matplotlib.pyplot as plt
import networkx as nx
import pydot
from networkx.drawing.nx_pydot import graphviz_layout


parse_tree_output_file = open("./parse_tree_output_1")
parse_tree_data = parse_tree_output_file.readlines()
parse_tree_output_file.close()
parsed = [x.split(". At node ") for x in parse_tree_data]
parsed = [[y.strip() for y in x] for x in parsed ]
idx_dict = {x[1]:0 for x in parsed}
root = parsed[0]
last = root
T = nx.Graph()
last_name = "'"+root[1]+"' {}".format(idx_dict[root[1]])
T.add_node(last_name)
idx_dict[root[1]] += 1
last_height = int(root[0])
stack = []
stack.append((last_height, last_name))
for i in range(1,len(parsed)):

    name = '"'+parsed[i][1]+str('" {}'.format(idx_dict[parsed[i][1]]))
    print(name)
    T.add_node(name)
    idx_dict[parsed[i][1]] +=1
    height = int(parsed[i][0])
    for j in reversed(stack):
        if(height> j[0]):
            last_height = j[0]
            last_name = j[1]
            break
        else:
            continue

    stack.append((height, name))
    T.add_edge(last_name, name)
    last_name = name
    last_height = height






# T = nx.balanced_tree(2, 5)

pos = graphviz_layout(T, prog="dot")
fig = plt.figure(figsize=(50,10))
fig.tight_layout()
nx.draw(T, pos, with_labels=True, font_size=9)
plt.savefig("./parse_tree_small.png",bbox_inches='tight')
