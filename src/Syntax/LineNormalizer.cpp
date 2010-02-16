#include <iostream> // for debugging
#include <cstdlib>

#include "LineNormalizer.h"

namespace Finch
{
    Ref<Token> LineNormalizer::ReadToken()
    {
        Ref<Token> token;
        
        while (token.IsNull())
        {
            token = mTokens.ReadToken();
            
            switch (token->Type())
            {
                case TOKEN_LINE:
                    if (mEatNewlines)
                    {
                        // discard any lines
                        token.Clear();
                    }
                    else
                    {
                        // discard newlines after first one
                        mEatNewlines = true;
                    }
                    break;

                // discard newlines after token that can't end expression
                case TOKEN_KEYWORD:
                case TOKEN_OPERATOR:
                case TOKEN_PIPE:
                case TOKEN_LEFT_ARROW:
                case TOKEN_DEF:
                case TOKEN_UNDEF:
                // discard newlines after open group
                case TOKEN_LEFT_PAREN:
                case TOKEN_LEFT_BRACKET:
                case TOKEN_LEFT_BRACE:
                    mEatNewlines = true;
                    break;
                    
                default:
                    mEatNewlines = false;
                    break;
            }
        }
        
        //std::cout << "norm " << *token << std::endl;
        
        return token;
    }
}