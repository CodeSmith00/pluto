#ifndef node_hpp
#define node_hpp

#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <optional>

#include "error.hpp"

enum ARGUMENT_EXPANSION
{
    None,
    Array,
    Dictionary,
};

extern std::vector<std::string> Operator_Preference;

class Node
{
    public:
        std::optional<Error> error;

        std::string type;
        int start;
        int end;

        Node();

        friend std::ostream &operator<<(std::ostream &os, const Node &n);
};

class Type : public Node
{
    public:
        std::string name;
        bool is_array;
        std::vector<Type> content;

        Type(std::string name, bool is_array, std::vector<Type> content);

        friend std::ostream &operator<<(std::ostream &os, const Type &data);
};

class Parameter : public Node
{
    public:
        Type type_data;
        std::string name;
        std::optional<Node*> default_argument;
        ARGUMENT_EXPANSION argument_expansion;

        Parameter(Type type_data, std::string name, std::optional<Node*> default_argument, ARGUMENT_EXPANSION argument_expansion);

        friend std::ostream &operator<<(std::ostream &os, const Parameter &data);
};

class Qualifier : public Node
{
    public:
        std::vector<std::string> qualifiers;

        Qualifier(std::vector<std::string> qualifiers);

        friend std::ostream &operator<<(std::ostream &os, const Qualifier &data);
};

class Literal : public Node
{
    public:
        std::optional<int> l_integer;
        std::optional<double> l_float;
        std::optional<std::string> l_string;

        Literal();

        friend std::ostream &operator<<(std::ostream &os, const Literal &data);
};

class CodeBlock : public Node
{
    public:
        std::optional<Type> return_type;
        std::vector<Parameter> parameters;
        std::vector<Node*> content;

        CodeBlock(std::optional<Type> return_type, std::vector<Parameter> parameters, std::vector<Node*> content);

        friend std::ostream &operator<<(std::ostream &os, const CodeBlock &data);
};

class Operation : public Node
{
    public:
        std::string operator_string;
        Node *left;
        Node *right;

        Operation(std::string operator_string, Node *left, Node *right);

        friend std::ostream &operator<<(std::ostream &os, const Operation &data);
};

class GetVariable : public Node
{
    public:
        std::string name;

        GetVariable(std::string name);

        friend std::ostream &operator<<(std::ostream &os, const GetVariable &data);
};

class AssignVariable : public Node
{
    public:
        Qualifier *qualifier;
        Type variable_type;
        std::string name;
        Node *value;

        AssignVariable(Qualifier *qualifier, Type variable_type, std::string name, Node *value);

        friend std::ostream &operator<<(std::ostream &os, const AssignVariable &data);
};

class FunctionCall : public Node
{
    public:
        std::string name;
        std::vector<Node*> arguments;

        FunctionCall(std::string name, std::vector<Node*> arguments);

        friend std::ostream &operator<<(std::ostream &os, const FunctionCall &data);
};

class IfStatement : public Node
{
    public:
        Node *if_expression;
        CodeBlock *if_code_block;
        std::vector<Node*> else_if_expressions;
        std::vector<CodeBlock*> else_if_code_blocks;
        CodeBlock *else_code_block;

        IfStatement(Node *if_expression, CodeBlock *if_code_block, std::vector<Node*> else_if_expressions, std::vector<CodeBlock*> else_if_code_blocks, CodeBlock *else_code_block);

        friend std::ostream &operator<<(std::ostream &os, const IfStatement &data);
};

class StatementEnd : public Node
{
    public:
        StatementEnd();

        friend std::ostream &operator<<(std::ostream &os, const StatementEnd &data);
};

#endif