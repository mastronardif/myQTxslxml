<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:csv="csv:csv">
<xsl:output method="text" encoding="utf-8" />
<xsl:strip-space elements="*" />

    <xsl:variable name="delimiter" select="','" />

    <xsl:variable name="cnt_S"  select="count(ssn)" />
    <xsl:variable name="cnt_P"  select="count(ssn/p)" />
    <xsl:variable name="cntVs"  select="count(ssn/p[1]/v)" />


<!--last Modified ______ 11:12AM
Purpose:  Used to ____ ,
-->

    <xsl:template match="/">
       <!-- cnt_S( <xsl:value-of select="$cnt_S"/> )
       cnt_P( <xsl:value-of select="$cnt_P"/> )
       cntVs( <xsl:value-of select="$cntVs"/> ) -->

    <xsl:text>BEGIN [SSN] </xsl:text> count(<xsl:value-of select="count(ssn)"/>)<xsl:text>&#xa;</xsl:text>
    <xsl:call-template  name="LIST"> 
        <xsl:with-param name="match" select="ssn"/>  
        <xsl:with-param name="cntPElems"  select="1"/>
        <xsl:with-param name="cntElems"  select="1"/>
    </xsl:call-template>

    <xsl:text>END [SSN]&#xa;</xsl:text>
    <xsl:text>BEGIN [SSN/P] </xsl:text> count(<xsl:value-of select="count(ssn/p)"/>)<xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="LIST">
        <xsl:with-param name="match" select="ssn/p"/>
        <xsl:with-param name="cntPElems"   select="$cnt_S"/>
        <xsl:with-param name="cntElems"   select="$cnt_P"/>  
    </xsl:call-template>
    <xsl:text>END [SSN/P]&#xa;</xsl:text>

    <xsl:text>BEGIN [SSN/P/V] </xsl:text> count(<xsl:value-of select="count(ssn/p/v)"/>)<xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="LIST"> 
        <xsl:with-param name="match"      select="ssn/p/v"/>
        <xsl:with-param name="cntPElems"  select="$cnt_P"/>
        <xsl:with-param name="cntElems"   select="$cntVs"/>
    </xsl:call-template>
    <xsl:text>END [SSN/P/V]&#xa;</xsl:text>

  </xsl:template>

    

<xsl:template name="LIST">
    <xsl:param name="match"/>
    <xsl:param name="cntPElems"/>   
    <xsl:param name="cntElems"/>

<xsl:variable name="numofElems" select="$cntElems" />


    <xsl:for-each select="$match">
        <!-- Header -->
        
        <xsl:if test="position() = 1">

            <xsl:value-of select="concat(name(.),'_id', $delimiter)"/>

            <xsl:for-each select="./@*">
                <xsl:value-of select="name(.)"/><xsl:value-of select="$delimiter"/>
            </xsl:for-each>

            <!-- Parenet ID-->  

            <xsl:value-of select="concat(name(./..),'_id', $delimiter)"/>
            <xsl:text>&#xa;</xsl:text>
    
        </xsl:if>

        <!-- Rows -->     
        <xsl:text>"</xsl:text><xsl:value-of select="position()-1"/><xsl:text>"</xsl:text><xsl:text>,</xsl:text>
        <xsl:for-each select="./@*">
            <xsl:text>"</xsl:text><xsl:value-of select="."/><xsl:text>"</xsl:text><xsl:value-of select="$delimiter"/>
        </xsl:for-each>

        <!-- Parenet ID -->  
        <xsl:text>"</xsl:text><xsl:value-of select="ceiling(position() div ($cntElems))"/><xsl:text>"</xsl:text><xsl:value-of select="$delimiter"/>
        <!--
        floor(position() div ($cntElems))
        <xsl:text>"</xsl:text><xsl:value-of select="floor(position() div (1+$cntElems) ) mod $cntPElems"/><xsl:text>"</xsl:text><xsl:value-of select="$delimiter"/>

        <xsl:text>"</xsl:text><xsl:value-of select="count(../preceding-sibling::*)+1"/><xsl:text>"</xsl:text><xsl:value-of select="$delimiter"/>
        -->
        <xsl:text>&#xa;</xsl:text>

    </xsl:for-each>

</xsl:template>    

</xsl:stylesheet>
