#pragma once
#include <string>
#include <vector>
#include <memory>
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual std::string kind() const = 0;
};
using NodePtr = std::unique_ptr<ASTNode>;
using NodeList = std::vector<NodePtr>;
struct ProgramNode : ASTNode {
    NodeList blocks;
    std::string kind() const override { return "Program"; }
};

struct DataEntryNode : ASTNode {
    std::string name;   
    std::string value;  
    std::string dataType; 
    std::vector<std::string> arrayItems; 
    std::string kind() const override { return "DataEntry"; }
};

struct DataBlockNode : ASTNode {
    std::vector<std::unique_ptr<DataEntryNode>> entries;
    std::string kind() const override { return "DataBlock"; }
};

struct CalcExprNode : ASTNode {
    std::string lhs;  
    std::string expr;  
    std::string kind() const override { return "CalcExpr"; }
};

struct CalcBlockNode : ASTNode {
    std::vector<std::unique_ptr<CalcExprNode>> exprs;
    std::string kind() const override { return "CalcBlock"; }
};

struct ExprNode : ASTNode {
    std::string raw; 
    std::string kind() const override { return "Expr"; }
};

struct PrintNode : ASTNode {
    std::unique_ptr<ExprNode> expr;
    std::string kind() const override { return "Print"; }
};

struct AssignNode : ASTNode {
    std::string varName;
    std::unique_ptr<ExprNode> value;
    std::string kind() const override { return "Assign"; }
};

struct IfNode : ASTNode {
    std::unique_ptr<ExprNode> condition;
    NodeList thenBody;
    NodeList elseBody;
    std::string kind() const override { return "If"; }
};

struct WhileNode : ASTNode {
    std::unique_ptr<ExprNode> condition;
    NodeList body;
    std::string kind() const override { return "While"; }
};

struct RepeatNode : ASTNode {
    int times = 0;
    NodeList body;
    std::string kind() const override { return "Repeat"; }
};

struct LogicBlockNode : ASTNode {
    NodeList statements;
    std::string kind() const override { return "LogicBlock"; }
};

struct OutLineNode : ASTNode {
    std::string tmpl; 
    std::string kind() const override { return "OutLine"; }
};

struct OutBlockNode : ASTNode {
    std::vector<std::unique_ptr<OutLineNode>> lines;
    std::string kind() const override { return "OutBlock"; }
};

struct FlowStepNode : ASTNode {
    std::string from;
    std::string to;
    std::string condition; 
    std::string kind() const override { return "FlowStep"; }
};

struct FlowBlockNode : ASTNode {
    std::string entry; 
    std::vector<std::unique_ptr<FlowStepNode>> steps;
    std::string kind() const override { return "FlowBlock"; }
};
