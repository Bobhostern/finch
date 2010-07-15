#pragma once

#include <iostream>

#include "CodeBlock.h"
#include "Expr.h"
#include "Macros.h"
#include "Object.h"
#include "Ref.h"
#include "Scope.h"
#include "FinchString.h"

namespace Finch
{
    using std::ostream;
    
    // Object class for a block: an invokable expression and the scope that
    // encloses it.
    class BlockObject : public Object
    {
    public:
        BlockObject(Ref<Object> parent, const CodeBlock & code,
                    Ref<Scope> closure, Ref<Object> self)
        :   Object(parent),
            mCode(code),
            mClosure(closure),
            mSelf(self)
        {}
        
        // Gets the names of the parameters this block takes.
        const Array<String> & Params() const { return mCode.Params(); }

        // Gets the scope enclosing the definition of this block.
        Ref<Scope> Closure() const { return mClosure; }
        
        bool IsMethod() const { return !mSelf.IsNull(); }
        
        // Gets the object owning the method enclosing the definition of this
        // block.
        Ref<Object> Self() const { return mSelf; }

        // Gets the compiled bytecode for the block.
        const CodeBlock & GetCode() const { return mCode; } 
        
        virtual BlockObject * AsBlock() { return this; }
        
        virtual void Trace(ostream & stream) const
        {
            stream << "block";
        }
        
    private:
        const CodeBlock & mCode;
              Ref<Scope>  mClosure;
              Ref<Object> mSelf;
    };
}

