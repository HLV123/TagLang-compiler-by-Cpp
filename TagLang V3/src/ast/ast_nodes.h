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
    std::string entry; // label bắt đầu
    std::vector<std::unique_ptr<FlowStepNode>> steps;
    std::string kind() const override { return "FlowBlock"; }
};

struct RAssignNode : ASTNode {
    std::string lhs;
    std::string rhs;
    std::string kind() const override { return "RAssign"; }
};
struct RVecNode : ASTNode {
    std::string name;
    std::vector<std::string> elements;
    std::string kind() const override { return "RVec"; }
};
struct RPrintNode : ASTNode {
    std::string expr;
    std::string kind() const override { return "RPrint"; }
};
struct RScriptBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "RScriptBlock"; }
};

struct JsonFieldNode : ASTNode {
    std::string key;
    std::string value;
    std::string valueType; 
    std::string kind() const override { return "JsonField"; }
};
struct JsonObjNode : ASTNode {
    std::string name;
    std::vector<std::unique_ptr<JsonFieldNode>> fields;
    std::string kind() const override { return "JsonObj"; }
};
struct JsonStringifyNode : ASTNode {
    std::string varName;
    std::string objName;
    std::string kind() const override { return "JsonStringify"; }
};
struct JsonParseNode : ASTNode {
    std::string varName;
    std::string jsonStr;
    std::string kind() const override { return "JsonParse"; }
};
struct JsonBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "JsonBlock"; }
};

struct PtrDeclNode : ASTNode {
    std::string type;  
    std::string name;
    std::string kind() const override { return "PtrDecl"; }
};
struct PtrAssignAddrNode : ASTNode {
    std::string ptrName;
    std::string varName;
    std::string kind() const override { return "PtrAssignAddr"; }
};
struct PtrDerefAssignNode : ASTNode {
    std::string ptrName;
    std::string value;
    std::string kind() const override { return "PtrDerefAssign"; }
};
struct PtrVarDeclNode : ASTNode {
    std::string type;
    std::string name;
    std::string value;
    std::string kind() const override { return "PtrVarDecl"; }
};
struct PtrPrintNode : ASTNode {
    std::string expr; 
    std::string kind() const override { return "PtrPrint"; }
};
struct PtrFuncNode : ASTNode {
    std::string funcName;
    std::string paramType;
    std::string paramName;
    NodeList body;
    std::string kind() const override { return "PtrFunc"; }
};
struct PtrCallNode : ASTNode {
    std::string funcName;
    std::string arg; 
    std::string kind() const override { return "PtrCall"; }
};
struct PtrBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "PtrBlock"; }
};

struct TryCatchNode : ASTNode {
    NodeList tryBody;
    std::string exceptionType;
    std::string exceptionVar;
    NodeList catchBody;
    NodeList finallyBody;
    std::string kind() const override { return "TryCatch"; }
};
struct ThrowNode : ASTNode {
    std::string exceptionType;
    std::string message;
    std::string kind() const override { return "Throw"; }
};
struct ErrorPrintNode : ASTNode {
    std::string expr;
    std::string kind() const override { return "ErrorPrint"; }
};
struct ErrorBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "ErrorBlock"; }
};

struct CArrayDeclNode : ASTNode {
    std::string elemType; 
    std::string name;
    int size = 0;
    std::vector<std::string> elements;
    std::string kind() const override { return "CArrayDecl"; }
};
struct CCharStrNode : ASTNode {
    std::string name;
    std::string value;
    bool isPtr = false; 
    std::string kind() const override { return "CCharStr"; }
};
struct CArrayPrintNode : ASTNode {
    std::string name;
    std::string index; 
    std::string kind() const override { return "CArrayPrint"; }
};
struct CArrayBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "CArrayBlock"; }
};

struct LambdaDeclNode : ASTNode {
    std::string name;
    std::vector<std::string> params;
    std::string body;
    std::string kind() const override { return "LambdaDecl"; }
};
struct LambdaCallNode : ASTNode {
    std::string resultVar;
    std::string lambdaName;
    std::vector<std::string> args;
    std::string kind() const override { return "LambdaCall"; }
};
struct LambdaPrintNode : ASTNode {
    std::string expr;
    std::string kind() const override { return "LambdaPrint"; }
};
struct LambdaBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "LambdaBlock"; }
};

struct ForRangeNode : ASTNode {
    std::string var;
    std::string from;
    std::string to;
    bool inclusive = false;
    std::string label; 
    NodeList body;
    std::string kind() const override { return "ForRange"; }
};
struct ForInNode : ASTNode {
    std::string var;
    std::string collection;
    std::string label;
    NodeList body;
    std::string kind() const override { return "ForIn"; }
};
struct LoopNode : ASTNode {
    std::string label;
    NodeList body;
    std::string kind() const override { return "Loop"; }
};
struct BreakNode : ASTNode {
    std::string label; 
    std::string kind() const override { return "Break"; }
};
struct IterWhileNode : ASTNode {
    std::string condition;
    NodeList body;
    std::string kind() const override { return "IterWhile"; }
};
struct IterPrintNode : ASTNode {
    std::string expr;
    std::string kind() const override { return "IterPrint"; }
};
struct IterBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "IterBlock"; }
};

struct ObjTableNode : ASTNode {
    std::string name;
    std::vector<std::pair<std::string,std::string>> fields; 
    std::string kind() const override { return "ObjTable"; }
};
struct ObjSetFieldNode : ASTNode {
    std::string objName;
    std::string field;  
    std::string value;
    bool isBracket = false;
    std::string kind() const override { return "ObjSetField"; }
};
struct ObjQueryNode : ASTNode {
    std::string varName;
    std::string objName;
    std::string method; 
    std::string arg;
    std::string kind() const override { return "ObjQuery"; }
};
struct ObjPrintNode : ASTNode {
    std::string expr;
    std::string kind() const override { return "ObjPrint"; }
};
struct ObjPrintRowNode : ASTNode {
    std::string objName;  
    std::string kind() const override { return "ObjPrintRow"; }
};
struct ObjBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "ObjBlock"; }
};

struct FuncDefNode : ASTNode {
    std::string name;
    std::vector<std::string> params;
    std::string retExpr;         
    NodeList    body;          
    std::string kind() const override { return "FuncDef"; }
};
struct FuncCallStmtNode : ASTNode {
    std::string resultVar;      
    std::string funcName;
    std::vector<std::string> args;
    std::string kind() const override { return "FuncCallStmt"; }
};
struct FuncAssignNode : ASTNode {
    std::string varName;
    std::string value;
    std::string kind() const override { return "FuncAssign"; }
};
struct FuncPrintNode : ASTNode {
    std::string expr;
    std::string kind() const override { return "FuncPrint"; }
};
struct FuncBlockNode : ASTNode {
    NodeList stmts;
    std::string kind() const override { return "FuncBlock"; }
};
