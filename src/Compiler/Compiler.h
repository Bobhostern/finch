#pragma once

#include <iostream>

#include "CodeBlock.h"
#include "Expr.h"
#include "Macros.h"
#include "IExprVisitor.h"
#include "Object.h"
#include "Ref.h"

namespace Finch
{
    class Environment;
    
    //### bob: wip
    // Compiles Finch ASTs to bytecode for execution by the interpreter.
    class Compiler : private IExprVisitor2
    {
    public:
        static void Compile(Environment & environment, const Expr & expr, CodeBlock & code);
        
    private:
        Compiler(Environment & environment, CodeBlock & code);
        
        virtual ~Compiler() {}
        
        virtual void Visit(const ArrayExpr & expr);
        virtual void Visit(const BlockExpr & expr);
        virtual void Visit(const DefExpr & expr);
        virtual void Visit(const KeywordExpr & expr);
        virtual void Visit(const NameExpr & expr);
        virtual void Visit(const NumberExpr & expr);
        virtual void Visit(const OperatorExpr & expr);
        virtual void Visit(const SequenceExpr & expr);
        virtual void Visit(const SelfExpr & expr);
        virtual void Visit(const SetExpr & expr);
        virtual void Visit(const StringExpr & expr);
        virtual void Visit(const UnaryExpr & expr);
        virtual void Visit(const UndefineExpr & expr);
        
        Environment & mEnvironment;
        CodeBlock & mCode;
        
        NO_COPY(Compiler);
    };
}