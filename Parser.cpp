//
// Created by moisa on 6/15/2021.
//

#include "Parser.h"

Parser::Parser(const vector<Token *> &tokener) : tokener(tokener) {}

void Parser::print() {
    for(auto & i : tokener){
        cout << i->toString();
    }
}

void Parser::advance() {
    index++;
}

bool Parser::Match(TokenType token, TokenType tokenType) {
    bool match;
    if(token == tokenType){
        match = true;
    }
    else{
        match = false;
    }
    return match;
}

void Parser::parseDatalog() {
    try{
        if(Match(tokener[index]->getType(), TokenType::SCHEMES)){
            parseTerminal(tokener, TokenType::SCHEMES);
            parseTerminal(tokener, TokenType::COLON);
            parseScheme();
            parseSchemeList();
            parseTerminal(tokener, TokenType::FACTS);
            parseTerminal(tokener, TokenType::COLON);
            parseFactList();
            parseTerminal(tokener, TokenType::RULES);
            parseTerminal(tokener, TokenType::COLON);
            parseRuleList();
            parseTerminal(tokener, TokenType::QUERIES);
            parseTerminal(tokener, TokenType::COLON);
            parseQuery();
            parseQueryList();
            parseTerminal(tokener, TokenType::EOF_TOKEN);
            //cout << "Success!" << endl;
            //cout << datalog.toString();
        }
    }

    catch(string &myType){
        cout << "Failure! " << endl;
        cout << "  " << myType;
    }
}

void Parser::parseTerminal(vector<Token *> tokens, TokenType type) {
    if(Match(tokens[index]->getType(), type)){
        advance();
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseScheme() {
    //scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    if(Match(tokener[index]->getType(), TokenType::ID)){
        Predicate SchemesPredicate(tokener[index]->getValue()); //Sets name for Predicate
        Parameter SchemesParameter;
        parseTerminal(tokener, TokenType::ID);
        parseTerminal(tokener, TokenType::LEFT_PAREN);
        SchemesParameter.setParameter(tokener[index]->getValue());  //Sets first parameter
        SchemesPredicate.addToPredicateList(SchemesParameter);  //Adds first parameter to Schemes vector
        parseTerminal(tokener, TokenType::ID);
        parseIDList();
        for(int i = 0; i < (int)parameterListTemp.size(); i++){
            SchemesPredicate.addToPredicateList(parameterListTemp.at(i));
        }
        parameterListTemp.clear(); //Clears Temp vector that carries the rest of parameters
        parseTerminal(tokener, TokenType::RIGHT_PAREN);
        datalog.addToSchemes(SchemesPredicate);
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseSchemeList() {
    //schemeList	->	scheme schemeList | lambda //FollowSet //If-else
    if(Match(tokener[index]->getType(), TokenType::ID)){
        parseScheme();
        parseSchemeList();
    }
    else if (Match(tokener[index]->getType(), TokenType::FACTS)){ //FOLLOW SET
        return; //LAMBDA
    }
    else{
        throw tokener[index]->toString();
    }
}



void Parser::parseIDList() {
    //idList  	-> 	COMMA ID idList | lambda
    if(Match(tokener[index]->getType(), TokenType::COMMA)){
        Parameter newParameter;
        parseTerminal(tokener, TokenType::COMMA);
        newParameter.setParameter(tokener[index]->getValue()); //Sets parameter
        parseTerminal(tokener, TokenType::ID);
        parameterListTemp.push_back(newParameter);
        parseIDList();
    }
    else if(Match(tokener[index]->getType(), TokenType::RIGHT_PAREN)){
        return;
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseFactList() {
    //factList	->	fact factList | lambda
    if(Match(tokener[index]->getType(), TokenType::ID)){
        parseFact();
        parseFactList();
    }
    else if(Match(tokener[index]->getType(), TokenType::RULES)){
        return;
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseFact() {
    //fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    if(Match(tokener[index]->getType(), TokenType::ID)){
        Predicate FactsPredicate(tokener[index]->getValue());
        Parameter FactsParameter;
        parseTerminal(tokener, TokenType::ID);
        parseTerminal(tokener, TokenType::LEFT_PAREN);
        FactsParameter.setParameter(tokener[index]->getValue());  //Sets first parameter
        FactsPredicate.addToPredicateList(FactsParameter);  //Adds first parameter to Facts vector
        datalog.addToDomain(FactsParameter.toString());
        parseTerminal(tokener, TokenType::STRING);
        parseStringList();
        for(int i = 0; i < (int)parameterListTemp.size(); i++){
            FactsPredicate.addToPredicateList(parameterListTemp.at(i));
            datalog.addToDomain(parameterListTemp.at(i).toString());
        }
        parameterListTemp.clear(); //Clears Temp vector that carries the rest of parameters
        parseTerminal(tokener, TokenType::RIGHT_PAREN);
        parseTerminal(tokener, TokenType::PERIOD);
        datalog.addToFacts(FactsPredicate);
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseStringList() {
    //stringList	-> 	COMMA STRING stringList | lambda
    if(Match(tokener[index]->getType(), TokenType::COMMA)){
        Parameter newParameter;
        parseTerminal(tokener, TokenType::COMMA);
        newParameter.setParameter(tokener[index]->getValue()); //Sets parameter
        parseTerminal(tokener, TokenType::STRING);
        parameterListTemp.push_back(newParameter);  //Adds parameter to temp vector
        parseStringList();
    }
    else if(Match(tokener[index]->getType(), TokenType::RIGHT_PAREN)){
        return;
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseRuleList() {
    //ruleList	->	rule ruleList | lambda
    if(Match(tokener[index]->getType(), TokenType::ID)){
        parseRule();
        TempPredicate.clear();
        parseRuleList();

    }
    else if(Match(tokener[index]->getType(), TokenType::QUERIES)){
        return;
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseRule() {
    //rule    	->	headPredicate COLON_DASH predicate parameterList PERIOD
    if(Match(tokener[index]->getType(), TokenType::ID)){
        Rule newRule;
        parseHeadPredicate();
        newRule.setRuleHeadID(TempPredicate.getID());
        newRule.setRuleHeadBody(TempPredicate.getParameters());
        TempPredicate.clear();
        parseTerminal(tokener, TokenType::COLON_DASH);
        parsePredicate();
        parsePredicateList();
        newRule.CreatePredicateVector(RuleListTemp);
        RuleListTemp.clear();
        TempPredicate.clear();
        parseTerminal(tokener, TokenType::PERIOD);
        datalog.addToRules(newRule);
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseHeadPredicate() {
    //headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    if(Match(tokener[index]->getType(), TokenType::ID)){
        Parameter newParameter;
        parameterListTemp.clear();
        TempPredicate.setPredicateName(tokener[index]->getValue());
        parseTerminal(tokener, TokenType::ID);
        parseTerminal(tokener, TokenType::LEFT_PAREN);
        newParameter.setParameter(tokener[index]->getValue());
        TempPredicate.addToPredicateList(newParameter); //Sets parameter
        parseTerminal(tokener, TokenType::ID);
        parseIDList();
        for(int i = 0; i < (int)parameterListTemp.size(); i++){
            TempPredicate.addToPredicateList(parameterListTemp.at(i));
        }
        parameterListTemp.clear();
        parseTerminal(tokener, TokenType::RIGHT_PAREN);
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parsePredicate() {
    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    if(Match(tokener[index]->getType(), TokenType::ID)) {
        parameterListTemp.clear();
        TempPredicate.clear();
        TempPredicate.setPredicateName(tokener[index]->getValue());
        parseTerminal(tokener, TokenType::ID);
        parseTerminal(tokener, TokenType::LEFT_PAREN);
        parseParameter();
        parseParameterList();
        for(int i = 0; i < (int)parameterListTemp.size(); i++){
            TempPredicate.addToPredicateList(parameterListTemp.at(i));
        }
        RuleListTemp.push_back(TempPredicate);
        parseTerminal(tokener, TokenType::RIGHT_PAREN);
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parsePredicateList() {
    //parameterList	->	COMMA predicate parameterList | lambda
    if(Match(tokener[index]->getType(), TokenType::COMMA)) {
        parseTerminal(tokener, TokenType::COMMA);
        parsePredicate();
        parsePredicateList();
    }
    else if(Match(tokener[index]->getType(), TokenType::PERIOD)) {
        return;
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseParameter() {
    //parameter	->	STRING | ID
    if (Match(tokener[index]->getType(), TokenType::STRING)) {
        Parameter newParameter;
        newParameter.setParameter(tokener[index]->getValue());
        newParameter.determineConstant(true);
        parameterListTemp.push_back(newParameter);
        parseTerminal(tokener, TokenType::STRING);
    } else if (!Match(tokener[index]->getType(), TokenType::STRING)) {
        Parameter newParameter;
        newParameter.setParameter(tokener[index]->getValue());
        newParameter.determineConstant(false);
        parameterListTemp.push_back(newParameter);
        parseTerminal(tokener, TokenType::ID);
    } else {
        throw tokener[index]->toString();
    }
}

void Parser::parseParameterList() {
    //parameterList	-> 	COMMA parameter parameterList | lambda
    if (Match(tokener[index]->getType(), TokenType::COMMA)) {
        parseTerminal(tokener, TokenType::COMMA);
        parseParameter();
        parseParameterList();
    }
    else if(Match(tokener[index]->getType(), TokenType::RIGHT_PAREN)) {
        return;
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseQuery() {
    //query	        ->      predicate Q_MARK
    if (Match(tokener[index]->getType(), TokenType::ID)) {
        Predicate QueryPredicate;
        parsePredicate();
        QueryPredicate.setPredicateName(TempPredicate.getID());
        QueryPredicate.setVector(TempPredicate.getParameters());
        parseTerminal(tokener, TokenType::Q_MARK);
        TempPredicate.clear();
        parameterListTemp.clear();  //Added This line WATCHOUT
        datalog.addToQueries(QueryPredicate);
    }
    else{
        throw tokener[index]->toString();
    }
}

void Parser::parseQueryList() {
    //queryList	->	query queryList | lambda
    if (Match(tokener[index]->getType(), TokenType::ID)) {
        parseQuery();
        parseQueryList();
    }
    else if(Match(tokener[index]->getType(), TokenType::EOF_TOKEN)) {
        return;
    }
    else{
        throw tokener[index]->toString();
    }
}

DatalogProgram Parser::getDatalog() {
    return datalog;
}




