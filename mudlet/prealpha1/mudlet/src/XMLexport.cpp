
/***************************************************************************
 *   Copyright (C) 2008 by Heiko Koehn  ( KoehnHeiko@googlemail.com )      *
 *                                                                         *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "XMLexport.h"

XMLexport::XMLexport( Host * pH )
: mpHost( pH )
, mType( "Host" )
{
    setAutoFormatting(true);
}

XMLexport::XMLexport( TTrigger * pT )
: mpTrigger( pT )
, mType( "Trigger" )
{
    setAutoFormatting(true);
}

XMLexport::XMLexport( TTimer * pT )
: mpTimer( pT )
, mType( "Timer" )
{
    setAutoFormatting(true);
}

XMLexport::XMLexport( TAlias * pT )
: mpAlias( pT )
, mType( "Alias" )
{
    setAutoFormatting(true);
}

XMLexport::XMLexport( TAction * pT )
: mpAction( pT )
, mType( "Action" )
{
    setAutoFormatting(true);
}

XMLexport::XMLexport( TScript * pT )
: mpScript( pT )
, mType( "Script" )
{
    setAutoFormatting(true);
}

XMLexport::XMLexport( TKey * pT )
: mpKey( pT )
, mType( "Key" )
{
    setAutoFormatting(true);
}

bool XMLexport::exportHost( QIODevice * device )
{
    setDevice(device);
    
    writeStartDocument();
    writeDTD("<!DOCTYPE MudletPackage>");
    
    writeStartElement( "MudletPackage" );
    writeAttribute("version", "1.0");
    
    writeStartElement( "HostPackage" );
    writeHost( mpHost );
    writeEndElement();
    
    writeEndElement();//MudletPackage
    writeEndDocument();
    return true;
}

bool XMLexport::writeHost( Host * pT )
{
    writeStartElement( "Host" );
    
    writeAttribute( "autoClearCommandLineAfterSend", pT->mAutoClearCommandLineAfterSend ? "yes" : "no" );
    writeAttribute( "disableAutoCompletion", pT->mDisableAutoCompletion ? "yes" : "no" );
    writeAttribute( "printCommand", pT->mPrintCommand ? "yes" : "no" );
    
    writeTextElement( "name", pT->mHostName );
    writeTextElement( "login", pT->mLogin );
    writeTextElement( "pass", pT->mPass );
    writeTextElement( "url", pT->mUrl );
    writeTextElement( "port", QString::number(pT->mPort) );
    writeTextElement( "wrapAt", QString::number(pT->mWrapAt) );
    writeTextElement( "wrapIndentCount", QString::number(pT->mWrapIndentCount) );
    writeTextElement( "commandSeperator", pT->mCommandSeperator );
    writeTextElement( "mFgColor", pT->mFgColor.name() );
    writeTextElement( "mBgColor", pT->mBgColor.name() );    
    writeTextElement( "mBlack", pT->mBlack.name() );    
    writeTextElement( "mLightBlack", pT->mLightBlack.name() );    
    writeTextElement( "mRed", pT->mRed.name() );    
    writeTextElement( "mLightRed", pT->mLightRed.name() );
    writeTextElement( "mBlue", pT->mBlue.name() );    
    writeTextElement( "mLightBlue", pT->mLightBlue.name() );    
    writeTextElement( "mGreen", pT->mGreen.name() );    
    writeTextElement( "mLightGreen", pT->mLightGreen.name() );    
    writeTextElement( "mYellow", pT->mYellow.name() );    
    writeTextElement( "mLightYellow", pT->mLightYellow.name() );    
    writeTextElement( "mCyan", pT->mCyan.name() );    
    writeTextElement( "mLightCyan", pT->mLightCyan.name() );    
    writeTextElement( "mMagenta", pT->mMagenta.name() );    
    writeTextElement( "mLightMagenta", pT->mLightMagenta.name() );    
    writeTextElement( "mWhite", pT->mWhite.name() );    
    writeTextElement( "mLightWhite", pT->mLightWhite.name() );    
    writeTextElement( "mDisplayFont", pT->mDisplayFont.toString() );    
    writeTextElement( "mCommandLineFont", pT->mCommandLineFont.toString() );    
    
    writeEndElement(); // end Host tag
    writeEndElement(); // end HostPackage tag
    
    writeStartElement( "TriggerPackage" );
    bool ret = true;   
    typedef list<TTrigger *>::const_iterator ItTriggerUnit;
    for( ItTriggerUnit it1 = pT->mTriggerUnit.mTriggerRootNodeList.begin(); it1 != pT->mTriggerUnit.mTriggerRootNodeList.end(); it1++)
    {
        TTrigger * pChildTrigger = *it1;
        ret = writeTrigger( pChildTrigger );
    }
    writeEndElement(); //end trigger package tag
    
    writeStartElement("TimerPackage");
    typedef list<TTimer *>::const_iterator ItTimerUnit;
    for( ItTimerUnit it2 = pT->mTimerUnit.mTimerRootNodeList.begin(); it2 != pT->mTimerUnit.mTimerRootNodeList.end(); it2++)
    {
        TTimer * pChildTimer = *it2;
        ret = writeTimer( pChildTimer );
    }
    writeEndElement();
    
    writeStartElement("AliasPackage");
    typedef list<TAlias *>::const_iterator ItAliasUnit;
    for( ItAliasUnit it3 = pT->mAliasUnit.mAliasRootNodeList.begin(); it3 != pT->mAliasUnit.mAliasRootNodeList.end(); it3++)
    {
        TAlias * pChildAlias = *it3;
        ret = writeAlias( pChildAlias );
    }
    writeEndElement();
    
    writeStartElement("ActionPackage");
    typedef list<TAction *>::const_iterator ItActionUnit;
    for( ItActionUnit it4 = pT->mActionUnit.mActionRootNodeList.begin(); it4 != pT->mActionUnit.mActionRootNodeList.end(); it4++)
    {
        TAction * pChildAction = *it4;
        ret = writeAction( pChildAction );
    }
    writeEndElement();
    
    writeStartElement("ScriptPackage");
    typedef list<TScript *>::const_iterator ItScriptUnit;
    for( ItScriptUnit it5 = pT->mScriptUnit.mScriptRootNodeList.begin(); it5 != pT->mScriptUnit.mScriptRootNodeList.end(); it5++)
    {
        TScript * pChildScript = *it5;
        ret = writeScript( pChildScript );
    }
    writeEndElement();
    
    writeStartElement("KeyPackage");
    typedef list<TKey *>::const_iterator ItKeyUnit;
    for( ItKeyUnit it6 = pT->mKeyUnit.mKeyRootNodeList.begin(); it6 != pT->mKeyUnit.mKeyRootNodeList.end(); it6++)
    {
        TKey * pChildKey = *it6;
        ret = writeKey( pChildKey );
    }
    writeEndElement();
}



bool XMLexport::exportTrigger( QIODevice * device )
{
    setDevice(device);
    
    writeStartDocument();
    writeDTD("<!DOCTYPE MudletPackage>");
    
    writeStartElement( "MudletPackage" );
    writeAttribute("version", "1.0");
    
    writeStartElement( "TriggerPackage" );
    writeTrigger( mpTrigger );
    writeEndElement();//TriggerPackage
    
    writeEndElement();//MudletPackage
    writeEndDocument();
    return true;
}


bool XMLexport::writeTrigger( TTrigger * pT )
{
    QString tag;
    if( pT->mIsFolder )
    {
        tag = "TriggerGroup";
    }
    else
    {
        tag = "Trigger";
    }
    writeStartElement( tag );
    writeAttribute( "isActive", pT->mIsActive ? "yes" : "no" );
    writeAttribute( "isFolder", pT->mIsFolder ? "yes" : "no" );
    writeAttribute( "isTempTrigger", pT->mIsTempTrigger ? "yes" : "no" ); 
    writeAttribute( "isMultiline", pT->mIsMultiline ? "yes" : "no" );
    writeTextElement( "name", pT->mName );
    writeTextElement( "script", pT->mScript );
    writeTextElement( "triggerType", QString::number( pT->mTriggerType ) );
    writeTextElement( "conditonLineDelta", QString::number( pT->mConditionLineDelta ) );
    writeStartElement( "regexCodeList" );
    for( int i=0; i<pT->mRegexCodeList.size(); i++ )
    {
        writeTextElement( "string", pT->mRegexCodeList[i] );
    }
    writeEndElement();
    
    writeStartElement( "regexCodePropertyList" );
    for( int i=0; i<pT->mRegexCodePropertyList.size(); i++ )
    {
        writeTextElement( "integer", QString::number( pT->mRegexCodePropertyList[i] ) );
    }
    writeEndElement();
    typedef list<TTrigger *>::const_iterator I;
    for( I it = pT->mpMyChildrenList->begin(); it != pT->mpMyChildrenList->end(); it++)
    {
        TTrigger * pChild = *it;
        writeTrigger( pChild );
    }
    writeEndElement();
    writeTextElement( "mCommand", pT->mCommand );
}


bool XMLexport::exportAlias( QIODevice * device )
{
    setDevice(device);
    
    writeStartDocument();
    writeDTD("<!DOCTYPE MudletPackage>");
    
    writeStartElement( "MudletPackage" );
    writeAttribute("version", "1.0");
    
    writeStartElement( "AliasPackage" );
    writeAlias( mpAlias );
    writeEndElement();
    
    writeEndElement();//MudletPackage
    writeEndDocument();
    return true;
}

bool XMLexport::writeAlias( TAlias * pT )
{
    QString tag;
    if( pT->mIsFolder )
    {
        tag = "AliasGroup";
    }
    else
    {
        tag = "Alias";
    }
    
    writeStartElement( tag );
    
    writeAttribute( "isActive", pT->mIsActive ? "yes" : "no" );
    writeAttribute( "isFolder", pT->mIsFolder ? "yes" : "no" );
    
    writeTextElement( "name", pT->mName );
    writeTextElement( "script", pT->mScript );
    writeTextElement( "command", pT->mCommand );
    writeTextElement( "regexCode", pT->mRegexCode );    
    
    typedef list<TAlias *>::const_iterator I;
    for( I it = pT->mpMyChildrenList->begin(); it != pT->mpMyChildrenList->end(); it++)
    {
        TAlias * pChild = *it;
        writeAlias( pChild );
    }
    writeEndElement();
}

bool XMLexport::exportAction( QIODevice * device )
{
    setDevice(device);
    
    writeStartDocument();
    writeDTD("<!DOCTYPE MudletPackage>");
    
    writeStartElement( "MudletPackage" );
    writeAttribute("version", "1.0");
    
    writeStartElement( "ActionPackage" );
    writeAction( mpAction );
    writeEndElement();
    
    writeEndElement();//MudletPackage
    writeEndDocument();
    return true;
}

bool XMLexport::writeAction( TAction * pT )
{
    QString tag;
    if( pT->mIsFolder )
    {
        tag = "ActionGroup";
    }
    else
    {
        tag = "Action";
    }
    
    writeStartElement( tag );
    
    writeAttribute( "isActive", pT->mIsActive ? "yes" : "no" );
    writeAttribute( "isFolder", pT->mIsFolder ? "yes" : "no" );
    writeAttribute( "isPushButton", pT->mIsPushDownButton ? "yes" : "no" );
    
    writeTextElement( "name", pT->mName );
    writeTextElement( "script", pT->mScript );
    writeTextElement( "commandButtonUp", pT->mCommandButtonUp );
    writeTextElement( "commandButtonDown", pT->mCommandButtonDown );    
    writeTextElement( "icon", pT->mIcon );    
    
    typedef list<TAction *>::const_iterator I;
    for( I it = pT->mpMyChildrenList->begin(); it != pT->mpMyChildrenList->end(); it++)
    {
        TAction * pChild = *it;
        writeAction( pChild );
    }
    writeEndElement();
}

bool XMLexport::exportTimer( QIODevice * device )
{
  
    setDevice(device);
    
    writeStartDocument();
    writeDTD("<!DOCTYPE MudletPackage>");
    
    writeStartElement( "MudletPackage" );
    writeAttribute("version", "1.0");
    
    writeStartElement( "TimerPackage" );
    writeTimer( mpTimer );
    writeEndElement();
    
    writeEndElement();//MudletPackage
    writeEndDocument();
    return true;
}

bool XMLexport::writeTimer( TTimer * pT )
{
    QString tag;
    if( pT->mIsFolder )
    {
        tag = "TimerGroup";
    }
    else
    {
        tag = "Timer";
    }
    
    writeStartElement( tag );
    
    writeAttribute( "isActive", pT->mUserActiveState ? "yes" : "no" );
    writeAttribute( "isFolder", pT->mIsFolder ? "yes" : "no" );
    writeAttribute( "isTempTimer", pT->mIsTempTimer ? "yes" : "no" );
    
    writeTextElement( "name", pT->mName );
    writeTextElement( "script", pT->mScript );
    writeTextElement( "command", pT->mCommand );
    writeTextElement( "time", pT->mTime.toString( "hh:mm:ss.zzz" ) );    
    
    typedef list<TTimer *>::const_iterator I;
    for( I it = pT->mpMyChildrenList->begin(); it != pT->mpMyChildrenList->end(); it++)
    {
        TTimer * pChild = *it;
        writeTimer( pChild );
    }
    writeEndElement();
}


bool XMLexport::exportScript( QIODevice * device )
{
    setDevice(device);
    
    writeStartDocument();
    writeDTD("<!DOCTYPE MudletPackage>");
    
    writeStartElement( "MudletPackage" );
    writeAttribute("version", "1.0");
    
    writeStartElement( "ScriptPackage" );
    writeScript( mpScript );
    writeEndElement();
    
    writeEndElement();//MudletPackage
    writeEndDocument();
    return true;
}

bool XMLexport::writeScript( TScript * pT )
{
    QString tag;
    if( pT->mIsFolder )
    {
        tag = "ScriptGroup";
    }
    else
    {
        tag = "Script";
    }
    
    writeStartElement( tag );
    
    writeAttribute( "isActive", pT->mIsActive ? "yes" : "no" );
    writeAttribute( "isFolder", pT->mIsFolder ? "yes" : "no" );
    
    writeTextElement( "name", pT->mName );
    writeTextElement( "script", pT->mScript );
    
    writeStartElement( "eventHandlerList" );
    for( int i=0; i<pT->mEventHandlerList.size(); i++ )
    {
        writeTextElement( "string", pT->mEventHandlerList[i] );
    }
    writeEndElement();
    
    typedef list<TScript *>::const_iterator I;
    for( I it = pT->mpMyChildrenList->begin(); it != pT->mpMyChildrenList->end(); it++)
    {
        TScript * pChild = *it;
        writeScript( pChild );
    }
    writeEndElement();
}


bool XMLexport::exportKey( QIODevice * device )
{
    setDevice(device);
    
    writeStartDocument();
    writeDTD("<!DOCTYPE MudletPackage>");
    
    writeStartElement( "MudletPackage" );
    writeAttribute("version", "1.0");
    
    writeStartElement( "KeyPackage" );
    writeKey( mpKey );
    writeEndElement();
    
    writeEndElement();//MudletPackage
    writeEndDocument();
    return true;
}

bool XMLexport::writeKey( TKey * pT )
{
    QString tag;
    if( pT->mIsFolder )
    {
        tag = "KeyGroup";
    }
    else
    {
        tag = "Key";
    }
    
    writeStartElement( tag );
    
    writeAttribute( "isActive", pT->mIsActive ? "yes" : "no" );
    writeAttribute( "isFolder", pT->mIsFolder ? "yes" : "no" );
    
    writeTextElement( "name", pT->mName );
    writeTextElement( "script", pT->mScript );
    writeTextElement( "command", pT->mCommand );
    writeTextElement( "keyCode", QString::number( pT->mKeyCode ) );
    writeTextElement( "keyModifier", QString::number( pT->mKeyModifier ) );    
    
    typedef list<TKey *>::const_iterator I;
    for( I it = pT->mpMyChildrenList->begin(); it != pT->mpMyChildrenList->end(); it++)
    {
        TKey * pChild = *it;
        writeKey( pChild );
    }
    writeEndElement();
}






